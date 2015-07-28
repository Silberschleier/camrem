//
// Created by Christopher Schmidt on 27.07.15.
//

#include "Http.h"

Http::Http(void) {
    BOOST_LOG_TRIVIAL(trace) << "Created HTTP instance.";
}

Http::~Http(void) {
    BOOST_LOG_TRIVIAL(trace) << "Removed HTTP instance.";
}

Http *Http::getInstance() {
    static Http instance;
    return &instance;
}