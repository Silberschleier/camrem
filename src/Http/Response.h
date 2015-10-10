//
// Created by Christopher Schmidt on 09.10.15.
//

#ifndef CAMREM_RESPONSE_H
#define CAMREM_RESPONSE_H

#include <string>

using std::string;

namespace Http {
    class Response {
    public:
        unsigned int status;
        Response();
        ~Response();
        virtual string *getContent() = 0;
        virtual bool is_static() = 0;
    };
}



#endif //CAMREM_RESPONSE_H
