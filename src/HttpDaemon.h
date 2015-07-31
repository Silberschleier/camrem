//
// Created by Christopher Schmidt on 30.07.15.
//

#ifndef CAMREM_HTTPDAEMON_H
#define CAMREM_HTTPDAEMON_H

#define MIN_PORT 1
#define MAX_PORT 65535

#include <string>
#include <stdlib.h>
#include <microhttpd.h>
#include "libs/json.hpp"
#include "Helpers.h"

using json = nlohmann::json;
using std::string;

class HttpDaemon {
private:
    struct MHD_Daemon *daemon;
    string *key_;
    string *cert_;
    uint port_;

public:
    HttpDaemon();
    ~HttpDaemon();
    bool init(json config);

};


#endif //CAMREM_HTTPDAEMON_H
