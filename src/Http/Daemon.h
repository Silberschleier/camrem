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

#ifndef CAMREM_HTTPDAEMON_H
#define CAMREM_HTTPDAEMON_H

#define MIN_PORT 1
#define MAX_PORT 65535

#include <string>
#include <stdlib.h>
#include <microhttpd.h>
#include "../json/src/json.hpp"
#include "../easylogging/src/easylogging++.h"
#include "../Helpers.h"
#include "Request.h"
#include "Http.h"

using json = nlohmann::json;
using std::string;

namespace Http {
    class Http;

    class Daemon {
    private:
        Http *http_;
        struct MHD_Daemon *daemon_;
        shared_ptr<string> key_;
        shared_ptr<string> cert_;
        uint port_;

        /*
         * MHD connection handler. For more details look into the documentation of MHD_AccessHandlerCallback.
         */
        static int handle_connection(
                void *cls,
                struct MHD_Connection *connection,
                const char *uri,
                const char *method,
                const char *version,
                const char *upload_data,
                size_t *upload_data_size,
                void **con_cls);

    public:
        Daemon(Http *http);

        /*
         * Initializes and starts the daemon.
         * @param Config to initialize the daemon with.
         */
        Daemon(Http *http, json config);
        ~Daemon();

        /*
         * Verifies the config and loads everything needed to run.
         * @param The Daemon config
         * @return True on success.
         */
        bool init(json config);

        /*
         * Starts the daemon.
         * @return false if the daemon is already running or an error occurs.
         */
        bool run();

    };
}


#endif //CAMREM_HTTPDAEMON_H
