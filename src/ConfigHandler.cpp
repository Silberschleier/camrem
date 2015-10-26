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

#include "ConfigHandler.h"

ConfigHandler::ConfigHandler() { }

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
