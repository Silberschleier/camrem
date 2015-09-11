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
#include "../libs/json.hpp"
#include "../Helpers.h"
#include "Context.h"

using json = nlohmann::json;
using std::string;

namespace Http {
    class Daemon {
    private:
        struct MHD_Daemon *daemon_;
        string *key_;
        string *cert_;
        uint port_;

        /*
         * MHD connection handler. For more details look into the documentation of MHD_AccessHandlerCallback.
         */
        static int handle_connection(
                void *cls,
                struct MHD_Connection *connection,
                const char *uri,
                const char *method,
                const char *version,
                const char *upload_data,
                size_t *upload_data_size,
                void **con_cls);

    public:
        Daemon();
        Daemon(json config);
        ~Daemon();

        /*
         * Verifies the config and loads everything needed to run.
         * @param The Daemon config
         * @return True on success.
         */
        bool init(json config);

        bool run();

    };
}


#endif //CAMREM_HTTPDAEMON_H
