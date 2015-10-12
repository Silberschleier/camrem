//
// Created by Christopher Schmidt on 27.07.15.
//

#include "Http.h"
#include "../ConfigHandler.h"


Http::Http::Http(void) {
    ConfigHandler *configHandler = ConfigHandler::getInstance();
    json path = configHandler->config["Http"]["DocumentRoot"];

    if ( not path.is_string() ) {
        BOOST_LOG_TRIVIAL(error) << "Invalid DocumentRoot.";
    } else {
        string t = path;
        document_root_ = t;
    }
}

Http::Http::~Http(void) {
    for ( auto item : daemons_ ) {
        delete item;
    }

    BOOST_LOG_TRIVIAL(trace) << "Removed HTTP instance.";
}

Http::Http *Http::Http::getInstance(void) {
    static Http instance;
    return &instance;
}

void Http::Http::run(void) {
    ConfigHandler *configHandler = ConfigHandler::getInstance();
    json config = configHandler->config["Http"];
    json vhosts = config["VirtualHosts"];

    // Check for faulty config
    if ( "" == document_root_ ) {
        BOOST_LOG_TRIVIAL(error) << "Faulty HTTP config. Not starting HTTP.";
    }

    if ( not vhosts.is_array() || vhosts.empty() ) {
        BOOST_LOG_TRIVIAL(info) << "No VirtualHosts defined.";
        return;
    }

    // Initialize and start each daemon
    BOOST_LOG_TRIVIAL(info) << "Starting VirtualHosts...";

    for (auto vhostConfig : vhosts) {
        daemons_.push_back( new Daemon(vhostConfig) );
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

bool Http::Http::processRequest(Request *request) {
    // Search if any handler matches the requested uri
    for ( auto handler : handlers_ ) {
        if ( regex_match( request->uri_, handler.first ) ) {
            // Check for faulty function calls
            if ( not handler.second ) return false;

            // Call the handler
            return handler.second(request);
        }
    }

    // No matching handler -> something went wrong!
    return false;
}
