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

#include <iostream>
#include <csignal>
#include "Helpers.h"
#include "ConfigHandler.h"
#include "Http/Http.h"
#include "Http/Daemon.h"
#include "Http/Bindings.h"
#include "Cam/Cam.h"

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
    srv->handleDirectory("webui", "");
    srv->handle("webui/index.html", std::regex("(/)"));

    srv->run();


    Cam::Cam cam;

    for(;;) sleep(1);
}