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

#include "Request.h"

Http::Request::Request(MHD_Connection *connection, const char *uri, const char *method) : uri_(uri), method_(method) {
    headers_ = json::object();
    getdata_ = json::object();
    cookies_ = json::object();
    postdata_ = "";
    response = NULL;

    MHD_get_connection_values(connection, MHD_GET_ARGUMENT_KIND, Request::process_connection_values, this);
    MHD_get_connection_values(connection, MHD_HEADER_KIND, Request::process_connection_values, this);
    MHD_get_connection_values(connection, MHD_COOKIE_KIND, Request::process_connection_values, this);
}

int Http::Request::process_connection_values(void *cls, enum MHD_ValueKind kind, const char *key, const char *value) {
    Request *request = (Request *) cls;
    string str_key(key);
    string str_val("");

    // Check for empty arguments
    if (NULL != value) {
        str_val = value;
    }

    // Decide where the data goes
    switch (kind) {
        case MHD_HEADER_KIND :          request->headers_[str_key] = str_val; break;
        case MHD_GET_ARGUMENT_KIND :    request->getdata_[str_key] = str_val; break;
        case MHD_COOKIE_KIND :          request->cookies_[str_key] = str_val; break;
        case MHD_RESPONSE_HEADER_KIND:break;
        case MHD_POSTDATA_KIND:break;
        case MHD_FOOTER_KIND:break;
    }

    return MHD_YES;
}

// TODO: Figure out why this does not get called
void Http::Request::completed(void *cls, struct MHD_Connection *connection, void **con_cls,
                              enum MHD_RequestTerminationCode toe) {
    std::cout << "Request deleted" << std::endl;
    if (NULL == con_cls ) return;

    Request *request = (Request *) *con_cls;
    delete request;
}

Http::Request::~Request() {

}
