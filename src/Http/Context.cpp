//
// Created by Christopher Schmidt on 03.08.15.
//

#include "Context.h"

Http::Context::Context(const char *uri, const char *method) : uri_(uri), method_(method) {
    headers = json::object();
    getdata = json::object();
    cookies = json::object();
}
