//
// Created by Christopher Schmidt on 27.07.15.
//

#ifndef CAMREM_HTTP_H
#define CAMREM_HTTP_H

#include <vector>
#include "../Helpers.h"
#include "Daemon.h"

using std::vector;

namespace Http {
    class Http {
    private:
        vector<Daemon*> daemons_;
        Http(void);
        ~Http(void);

    public:
        /*
         * The instance of Http is defined and created in here.
         * @return The instance of Http
         */
        static Http * getInstance(void);
        void run(void);
    };
}


#endif //CAMREM_HTTP_H
