//
// Created by Christopher Schmidt on 28.07.15.
//

#ifndef CAMREM_CONFIGHANDLER_H
#define CAMREM_CONFIGHANDLER_H

#include <fstream>
#include <string>
#include "Helpers.h"
#include "json/src/json.hpp"

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
