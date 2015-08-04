//
// Created by Christopher Schmidt on 03.08.15.
//

#include "HttpContext.h"

HttpContext::HttpContext(const char *uri, const char *method) : uri_(uri), method_(method) {
    headers = json::object();
    getdata = json::object();
    cookies = json::object();
}
