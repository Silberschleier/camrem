//
// Created by Christopher Schmidt on 27.07.15.
//

#include <iostream>
#include "Helpers.h"
#include "Http.h"

int main(int argc, const char * argv[]) {
    init_logging();
    BOOST_LOG_TRIVIAL(info) << "Camrem started.";

    Http* srv = Http::getInstance();

    signal(SIGINT, signal_handler);

    for(;;) sleep(1);
}