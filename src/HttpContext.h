//
// Created by Christopher Schmidt on 03.08.15.
//

#ifndef CAMREM_HTTPCONTEXT_H
#define CAMREM_HTTPCONTEXT_H

#include <string>
#include <microhttpd.h>
#include "libs/json.hpp"

using std::string;
using nlohmann::json;

class HttpContext {
private:
    string uri_;
    string method_;
    json headers;
    json getdata;
    json cookies;
public:
    HttpContext(const char *uri, const char *method);
};


#endif //CAMREM_HTTPCONTEXT_H
