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

#include "Http.h"
#include "../ConfigHandler.h"


Http::Http::Http(void) {
    ConfigHandler *configHandler = ConfigHandler::getInstance();
    json path = configHandler->config["Http"]["DocumentRoot"];

    if ( not path.is_string() ) {
        LOG(ERROR) << "Invalid DocumentRoot.";
    } else {
        string t = path;
        document_root_ = t;
    }
}

Http::Http::~Http(void) {
    for ( auto item : daemons_ ) {
        delete item;
    }

    LOG(TRACE) << "Removed HTTP instance.";
}

void Http::Http::run(void) {
    ConfigHandler *configHandler = ConfigHandler::getInstance();
    json config = configHandler->config["Http"];
    json vhosts = config["VirtualHosts"];

    // Check for faulty config
    if ( "" == document_root_ ) {
        LOG(ERROR) << "Faulty HTTP config. Not starting HTTP.";
    }

    if ( not vhosts.is_array() || vhosts.empty() ) {
        LOG(INFO) << "No VirtualHosts defined.";
        return;
    }

    // Initialize and start each daemon
    LOG(INFO) << "Starting VirtualHosts...";

    for (auto vhostConfig : vhosts) {
        daemons_.push_back(new Daemon(this, vhostConfig));
    }
}

void Http::Http::handle(function<bool(Request *)> callback, regex uri) {
    pair<regex, function<bool(Request *)>> handler = make_pair(uri, callback);
    handlers_.insert(handlers_.begin(), handler);
}

void Http::Http::handle(string filename, regex uri) {
    handle(filename, STATUS_OK, uri);
}

void Http::Http::handle(string filename, StatusCode status, regex uri) {
    auto callback = std::bind(Bindings::staticFile, std::placeholders::_1, document_root_ + "/" + filename, status);
    handle(callback, uri);
}

void Http::Http::handleDirectory(string path, string prefix) {
    string filepath;
    string fileuri;
    fs::path p( document_root_ + "/" + path );

    if ( fs::exists(p) && fs::is_directory(p) ) {

        // Loop through all directory entries
        for ( fs::directory_iterator end, entry(p); entry != end; entry++ ) {
            filepath = path + "/" + entry->path().filename().string();
            fileuri = prefix + "/" + entry->path().filename().string();

            // If the entry is a file,
            if ( fs::is_regular_file(entry->status()) ) {
                handle(filepath, regex( "(" + fileuri + ")"));
            }

            // If it is a directory, continue recursively
            if ( fs::is_directory(entry->status()) ) {
                handleDirectory(filepath, fileuri);
            }
        }
    } else {
        LOG(ERROR) << "'" << path << "' is not a directory. Skipping.";
    }
}


bool Http::Http::processRequest(Request *request) {
    std::smatch params;

    // Search if any handler matches the requested uri
    for ( auto handler : handlers_ ) {
        if ( regex_match( request->uri_, params, handler.first ) ) {
            // Check for faulty function calls
            if ( not handler.second ) return false;

            // Store parameters found in the uri
            request->uridata = params;

            // Call the handler
            return handler.second(request);
        }
    }

    // No matching handler -> something went wrong!
    return false;
}

