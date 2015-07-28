//
// Created by Christopher Schmidt on 27.07.15.
//

#include <iostream>
#include "Helpers.h"
#include "ConfigHandler.h"

int main(int argc, const char * argv[]) {
    init_logging();
    BOOST_LOG_TRIVIAL(info) << "Camrem started";

    ConfigHandler *conf = ConfigHandler::getInstance();
    if (not conf->init("/Users/chris/Git/camrem/config.json")) {
        BOOST_LOG_TRIVIAL(fatal) << "Error opening config";
        exit(1);
    }

    signal(SIGINT, signal_handler);

   // for(;;) sleep(1);
}