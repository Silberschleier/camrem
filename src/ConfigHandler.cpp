//
// Created by Christopher Schmidt on 28.07.15.
//

#include "ConfigHandler.h"

ConfigHandler::ConfigHandler() {

}

ConfigHandler::~ConfigHandler() {
    flush();
}

ConfigHandler *ConfigHandler::getInstance() {
    static ConfigHandler instance;
    return &instance;
}

bool ConfigHandler::init(string filename) {
    fstream fs;

    filename_ = filename;

    // Open filestream for config file
    fs.open(filename, fstream::in);

    // Check for success
    if (not fs.is_open()) {
        BOOST_LOG_TRIVIAL(warning) << "Could not open config file: " << filename;
        return false;
    }
    BOOST_LOG_TRIVIAL(trace) << "Opened config file for reading: " << filename;

    // Deserialize config
    try {
        config << fs;
    } catch (const std::invalid_argument& exception) {
        BOOST_LOG_TRIVIAL(warning) << "Error exists in config file: " << exception.what();
        return false;
    }
    BOOST_LOG_TRIVIAL(trace) << "Deserialized config";

    return true;
}

void ConfigHandler::flush() {
    fstream fs;
    BOOST_LOG_TRIVIAL(trace) << "Flushing config...";

    fs.open(filename_, fstream::out | fstream::trunc);

    // Check if the filestream is ok
    if (not fs.is_open()) {
        BOOST_LOG_TRIVIAL(warning) << "Could not open " << filename_ << " for writing";
        return;
    }

    fs.clear();
    fs << std::setw(2) << config;
}
