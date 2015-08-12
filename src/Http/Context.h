//
// Created by Christopher Schmidt on 03.08.15.
//

#ifndef CAMREM_HTTPCONTEXT_H
#define CAMREM_HTTPCONTEXT_H

#include <string>
#include <microhttpd.h>
#include "../libs/json.hpp"

using std::string;
using nlohmann::json;

namespace Http {
    class Context {
    private:
        string uri_;
        string method_;
        json headers_;
        json getdata_;
        json cookies_;

        /*
         * MHD parameter iterator. See MHD documentation for further information.
         */
        static int process_connection_values(void *cls, enum MHD_ValueKind kind, const char *key, const char *value);
    public:

        Context(MHD_Connection *connection, const char *uri, const char *method);

        string dumpJson();
    };
}


#endif //CAMREM_HTTPCONTEXT_H
