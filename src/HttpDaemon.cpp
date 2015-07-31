//
// Created by Christopher Schmidt on 30.07.15.
//

#include "HttpDaemon.h"

HttpDaemon::HttpDaemon() {

}

HttpDaemon::~HttpDaemon() {
   // TODO
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
