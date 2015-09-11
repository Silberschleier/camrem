//
// Created by Christopher Schmidt on 03.08.15.
//

#ifndef CAMREM_HTTPCONTEXT_H
#define CAMREM_HTTPCONTEXT_H

#include <string>
#include <microhttpd.h>
#include "../json/src/json.hpp"

#include "Daemon.h"

using std::string;
using nlohmann::json;

namespace Http {
    class Context {
    friend class Daemon;
    private:
        string uri_;
        string method_;
        string postdata_;
        json headers_;
        json getdata_;
        json cookies_;

        /*
         * MHD parameter iterator. See MHD documentation for further information.
         */
        static int process_connection_values(void *cls, enum MHD_ValueKind kind, const char *key, const char *value);
    public:

        Context(MHD_Connection *connection, const char *uri, const char *method);
        static void completed(void *cls, struct MHD_Connection *connection, void **con_cls, enum MHD_RequestTerminationCode toe);

        string dumpJson();
    };
}


#endif //CAMREM_HTTPCONTEXT_H
