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
#include "Request.h"
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

    class Daemon;
    class Request;

    class Http {
    private:
        vector<Daemon*> daemons_;
        vector<pair<regex, function<bool(Request *)>>> handlers_;
        string document_root_;

    public:
        Http(void);
        ~Http(void);

        /*
         * Initializes and runs every VirtualHost specified in the config.
         */
        void run(void);

        /*
         * Registers an URI and function to handle.
         * @param callback: The function to execute. The callback should return false, if an error occurs.
         * @param uri: The URIs to handle.
         */
        void handle(function<bool(Request *)> callback, regex uri);

        /*
         * Registers a static file to handle. Response code will always be STATUS_OK.
         * @param filename: Path to the file. Must be relative to document_root.
         * @param uri: The URIs to handle.
         */
        void handle(string filename, regex uri);

        /*
         * Registers a static file to handle.
         * @param filename: Path to the file. Must be relative to document_root.
         * @param status: The response code to return.
         * @param uri: The URIs to handle.
         */
        void handle(string filename, StatusCode status, regex uri);

        /*
         * Registers (recursively) the static files of a whole directory.
         * @param path: Path to the directory. Must be relative to document_root.
         * @param prefix: Prefix to the URI.
         */
        void handleDirectory(string path, string prefix);

        /*
         * Searches and executes the handler matching the URI of the given request.
         * @param request: The request to process.
         * @returns: The success of the handler, or false if no matching handler is found or callable.
         */
        bool processRequest(Request *request);
    };
}


#endif //CAMREM_HTTP_H
