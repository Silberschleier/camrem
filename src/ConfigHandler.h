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

#ifndef CAMREM_CONFIGHANDLER_H
#define CAMREM_CONFIGHANDLER_H

#include <fstream>
#include <string>
#include "Helpers.h"
#include "json/src/json.hpp"
#include "easylogging/src/easylogging++.h"

using std::string;
using std::fstream;
using json = nlohmann::json;

class ConfigHandler {
private:
    string filename_;

    ConfigHandler();

    /*
     * Saves the config before exit
     */
    ~ConfigHandler();

public:
    json config;

    /*
     * @return The instance of ConfigHandler
     */
    static ConfigHandler * getInstance();

    /*
     * Opens and de-serializes the config file.
     * @return true on success.
     */
    bool init(string filename);

    /*
     * Save volatile changes to disk
     */
    void flush();
};


#endif //CAMREM_CONFIGHANDLER_H
