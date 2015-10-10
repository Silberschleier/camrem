//
// Created by Christopher Schmidt on 27.07.15.
//

#ifndef CAMREM_HTTP_H
#define CAMREM_HTTP_H

#include <vector>
#include <regex>
#include "../Helpers.h"
#include "Daemon.h"
#include "Response.h"

using std::vector;
using std::regex;
using std::pair;
using std::regex_match;
using std::function;

namespace Http {
    class Http {
    private:
        vector<Daemon*> daemons_;
        vector<pair<regex, function<Response(Context*)>>> handlers_;
        Http(void);
        ~Http(void);

    public:
        /*
         * The instance of Http is defined and created in here.
         * @return The instance of Http
         */
        static Http * getInstance(void);
        /*
         * Initializes and runs every VirtualHost specified in the config.
         */
        void run(void);
        void handle(function<Response(Context*)> callback, regex uri);
        Response processRequest(Context *context);
    };
}


#endif //CAMREM_HTTP_H
