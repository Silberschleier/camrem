//
// Created by Christopher Schmidt on 30.07.15.
//

#include "HttpDaemon.h"

HttpDaemon::HttpDaemon() {

}

HttpDaemon::~HttpDaemon() {

}

bool HttpDaemon::init(json config) {
    // Check if the port is a valid number
    if ( not config["port"].is_number_integer() ) {
        BOOST_LOG_TRIVIAL(fatal) << "Invalid HTTP config: Port is not set or NaN";
        return false;
    }

    // Store port value for convenience
    port_ = config["port"];

    // Check if the port is in range
    if ( port_ < MIN_PORT || port_ > MAX_PORT ) {
        BOOST_LOG_TRIVIAL(fatal) << "Invalid HTTP config: Port must be between "
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
        BOOST_LOG_TRIVIAL(fatal) << "Invalid SSL config.";
        return false;
    }

    if ( not config["ssl"]["cert"].is_string() || not config["ssl"]["key"].is_string() ) {
        BOOST_LOG_TRIVIAL(fatal) << "Invalid SSL config.";
        return false;
    }

    // Load SSL key and certificate
    key_ = load_file(config["ssl"]["key"]);
    cert_ = load_file(config["ssl"]["cert"]);

    // Check if the files are loaded
    if ( key_ == NULL || cert_ == NULL ) {
        BOOST_LOG_TRIVIAL(fatal) << "Error loading keyfiles";
        return false;
    }

    return true;
}

int HttpDaemon::handle_connection(void *cls, struct MHD_Connection *connection, const char *uri, const char *method,
                                  const char *version, const char *upload_data, size_t *upload_data_size,
                                  void **con_cls) {
    struct MHD_Response *response;
    int ret, status;
    HttpContext *context;

    // Check if the context is created already, or create it.
    if ( NULL == *con_cls ) {
        context = new HttpContext(uri, method);
    } else {
        context = (HttpContext *) *con_cls;
    }




    // Process POST data

    // Get response from Http main class

    // Enqueue response and free resources

    const char *page = "test";
    response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);

    ret = MHD_queue_response(connection, 500, response);
    MHD_destroy_response(response);

    delete context;

    return ret;
}

int HttpDaemon::process_connection_values(void *cls, enum MHD_ValueKind kind, const char *key, const char *value) {
    // Check for empty arguments
    if ( NULL == value ) {
        ((json*) cls)[*key] = "";
    } else {
        ((json*) cls)[*key] = value;
    }

    return MHD_YES;
}

bool HttpDaemon::run() {
    // Check for already running daemons
    if ( NULL != daemon_ ) {
        return false;
    }

    daemon_ = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION, port_, NULL, NULL, &handle_connection, NULL, MHD_OPTION_END);

    if ( NULL == daemon_ ) {
        BOOST_LOG_TRIVIAL(warning) << "Could not bind http daemon to port " << port_;
        return false;
    }

    BOOST_LOG_TRIVIAL(info) << "Listening on port " << port_;
    return true;
}
