//
// Created by Christopher Schmidt on 09.10.15.
//

#ifndef CAMREM_RESPONSE_H
#define CAMREM_RESPONSE_H

#include <string>
#include <memory>

using std::string;
using std::shared_ptr;
using std::make_shared;

namespace Http {
    class Response {
    public:
        unsigned int status;
        shared_ptr<string> content;

        Response();
        ~Response();
        virtual shared_ptr<string> getContent();
        virtual bool is_static();
    };
}



#endif //CAMREM_RESPONSE_H
