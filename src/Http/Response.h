//
// Created by Christopher Schmidt on 09.10.15.
//

#ifndef CAMREM_RESPONSE_H
#define CAMREM_RESPONSE_H

#include <string>

using std::string;

namespace Http {
    class Response {
        friend class Daemon;
    private:
        unsigned int status_;
        string content_;
    public:
        Response();
        ~Response();
    };
}



#endif //CAMREM_RESPONSE_H
