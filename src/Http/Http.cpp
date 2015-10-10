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

void Http::Http::handle(function<Response(Context*)> callback, regex uri) {
    pair<regex, function<Response(Context*)>> handler = make_pair(uri, callback);
    handlers_.insert(handlers_.begin(), handler);
}

Http::Response Http::Http::processRequest(Context *context) {
    for ( auto handler : handlers_ ) {
        if ( regex_match( context->uri_, handler.first) ) {
            return handler.second(context);
        }
    }

    // TODO: Return error page
    return Response();
}
