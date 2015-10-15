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

#ifndef CAMREM_HTTP_H
#define CAMREM_HTTP_H

#include <vector>
#include <regex>
#include <boost/filesystem.hpp>
#include "../Helpers.h"
#include "Daemon.h"
#include "Response.h"
#include "Bindings.h"

using std::vector;
using std::regex;
using std::pair;
using std::regex_match;
using std::function;

namespace fs = boost::filesystem;

namespace Http {
    enum StatusCode {
        STATUS_OK = 200,
        STATUS_NOTFOUND = 404,
        STATUS_SERVERERROR = 500
    };

    class Http {
    private:
        vector<Daemon*> daemons_;
        vector<pair<regex, function<bool(Request *)>>> handlers_;
        string document_root_;
        Http(void);
        ~Http(void);

    public:
        /*
         * The instance of Http is defined and created in here.
         * @return The instance of Http
         */
        static Http * getInstance(void);
        /*
         * Initializes and runs every VirtualHost specified in the config.
         */
        void run(void);
        void handle(function<bool(Request *)> callback, regex uri);
        void handle(string filename, regex uri);
        void handle(string filename, StatusCode status, regex uri);
        void handleDirectory(string path, string prefix);
        bool processRequest(Request *request);
    };
}


#endif //CAMREM_HTTP_H
