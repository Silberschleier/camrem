//
// Created by Christopher Schmidt on 27.07.15.
//

#include <iostream>
#include <csignal>
#include "Helpers.h"
#include "ConfigHandler.h"
#include "Http/Http.h"
#include "Http/Daemon.h"
#include "Http/Bindings.h"

int main(int argc, const char * argv[]) {
    init_logging();
    BOOST_LOG_TRIVIAL(info) << "Camrem started.";

    ConfigHandler *conf = ConfigHandler::getInstance();
    if (not conf->init("config.json")) {
        BOOST_LOG_TRIVIAL(fatal) << "Error opening config";
        exit(1);
    }

    signal(SIGINT, signal_handler);

    Http::Http* srv = Http::Http::getInstance();
    srv->handle("404.html", Http::STATUS_NOTFOUND, std::regex("(.*)"));
    srv->handle(Http::Bindings::jsonNotFound, std::regex("(/api/)(.*)"));
    srv->handleDirectory("webui", "/webui");

    srv->run();

    for(;;) sleep(1);
}