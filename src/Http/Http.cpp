//
// Created by Christopher Schmidt on 27.07.15.
//

#include "Http.h"
#include "../ConfigHandler.h"


Http::Http::Http(void) {
    BOOST_LOG_TRIVIAL(trace) << "Created HTTP instance.";
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
    ConfigHandler *configHandler = ConfigHandler::getInstance();
    json doc_root = configHandler->config["Http"]["DocRoot"];

    // TODO: Check DocRoot somewhere else
    if ( not doc_root.is_string() || doc_root == "" ) {
        BOOST_LOG_TRIVIAL(error) << "Invalid DocRoot.";
        return;
    }

    string path = doc_root;

    auto callback = std::bind(Bindings::staticFile, std::placeholders::_1, path + "/" + filename);
    pair<regex, function<bool(Request*)>> handler = make_pair(uri, callback);
    handlers_.insert(handlers_.begin(), handler);
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
