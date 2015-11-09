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

#ifndef CAMREM_HTTPCONTEXT_H
#define CAMREM_HTTPCONTEXT_H

#include <string>
#include <memory>
#include <microhttpd.h>
#include "../json/src/json.hpp"
#include "../easylogging/src/easylogging++.h"

#include "Daemon.h"
#include "Response.h"

using std::shared_ptr;
using std::string;
using nlohmann::json;

namespace Http {
    class Request {
        friend class Daemon;
        friend class Http;
    private:
        string uri_;
        string method_;
        string postdata_;
        json headers_;
        json getdata_;
        json cookies_;


        /*
         * MHD parameter iterator. See MHD documentation for further information.
         */
        static int process_connection_values(void *cls, enum MHD_ValueKind kind, const char *key, const char *value);
    public:
        shared_ptr<Response> response;

        Request(MHD_Connection *connection, const char *uri, const char *method);
        ~Request();

        /*
         * Clean up after completion of a request. See MHD documentation for further information.
         */
        static void completed(void *cls, struct MHD_Connection *connection, void **con_cls, enum MHD_RequestTerminationCode toe);

    };
}


#endif //CAMREM_HTTPCONTEXT_H
