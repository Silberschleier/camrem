/*
    Copyright (C) 2015  Christopher Schmidt

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "Daemon.h"
#include "Http.h"

Http::Daemon::Daemon(Http *http) : http_(http) {
    daemon_ = NULL;
}

Http::Daemon::Daemon(Http *http, json config) : http_(http) {
    daemon_ = NULL;

    this->init(config);
    this->run();
}

Http::Daemon::~Daemon() {
    MHD_stop_daemon(daemon_);
}

bool Http::Daemon::init(json config) {
    // Check if the port is a valid number
    if ( not config["port"].is_number_integer() ) {
        LOG(FATAL) << "Invalid HTTP config: Port is not set or NaN";
        return false;
    }

    // Store port value for convenience
    port_ = config["port"];

    // Check if the port is in range
    if ( port_ < MIN_PORT || port_ > MAX_PORT ) {
        LOG(FATAL) << "Invalid HTTP config: Port must be between "
                                 << MIN_PORT << " and " << MAX_PORT
                                 << ", but is " << port_;
        return false;
    }

    // Check if SSL is enabled, if not we're done here.
    if ( config["ssl"].is_boolean() && not config["ssl"] ) {
        return true;
    }

    // Check if the SSL config appears to be valid
    if ( not config["ssl"].is_object() ) {
        LOG(FATAL) << "Invalid SSL config.";
        return false;
    }

    if ( not config["ssl"]["cert"].is_string() || not config["ssl"]["key"].is_string() ) {
        LOG(FATAL) << "Invalid SSL config.";
        return false;
    }

    // Load SSL key and certificate
    key_ = load_file(config["ssl"]["key"]);
    cert_ = load_file(config["ssl"]["cert"]);

    // Check if the files are loaded
    if ( key_ == NULL || cert_ == NULL ) {
        LOG(FATAL) << "Error loading keyfiles";
        return false;
    }

    return true;
}

int Http::Daemon::handle_connection(void *cls, struct MHD_Connection *connection, const char *uri, const char *method,
                                  const char *version, const char *upload_data, size_t *upload_data_size,
                                  void **con_cls) {
    struct MHD_Response *mhd_response;
    int ret;
    unsigned int status;
    Request *request;
    shared_ptr<Response> response;
    Daemon *daemon = (Daemon*) cls;

    // Check if the request is created already, or create it.
    if ( NULL == *con_cls ) {
        request = new Request(connection, uri, method);
        *con_cls = (void *) request;
        return MHD_YES;
    } else {
        request = (Request *) *con_cls;
    }

    // Process POST/PUT data
    // TODO: Check for max_upload_size
    if ( *upload_data_size > 0 ) {
        request->postdata_.append(upload_data);
        *upload_data_size = 0;

        return MHD_YES;
    }

    // Process the request in Http main class
    if ( daemon->http_->processRequest(request) ) {
        response = request->response;
        status = response->status;

        mhd_response = MHD_create_response_from_buffer(response->getRawDataSize(),
                                                       (void*) response->getRawData(),
                                                       MHD_RESPMEM_PERSISTENT);
    } else {
        const char *error = "Internal Server Error";
        status = STATUS_SERVERERROR;

        mhd_response = MHD_create_response_from_buffer(strlen(error), (void*) error, MHD_RESPMEM_PERSISTENT);
    }

    // Enqueue response and free resources
    ret = MHD_queue_response(connection, status, mhd_response);
    MHD_destroy_response(mhd_response);
    delete request;

    return ret;
}

bool Http::Daemon::run() {
    // Check for already running daemons
    if ( NULL != daemon_ ) {
        return false;
    }

    daemon_ = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION, port_, NULL, NULL,
                               &handle_connection, this, NULL,
                               MHD_OPTION_NOTIFY_COMPLETED, Request::completed, NULL,
                               MHD_OPTION_END);

    if ( NULL == daemon_ ) {
        LOG(WARNING) << "Could not bind http daemon to port " << port_;
        return false;
    }

    LOG(INFO) << "Listening on port " << port_;
    return true;
}

