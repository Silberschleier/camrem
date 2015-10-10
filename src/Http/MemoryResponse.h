//
// Created by Christopher Schmidt on 10.10.15.
//

#ifndef CAMREM_MEMORYRESPONSE_H
#define CAMREM_MEMORYRESPONSE_H

#include "Response.h"

namespace Http {
    class MemoryResponse : public Response {
    public:
        string content;
        string *getContent();
        bool is_static();
    };
}


#endif //CAMREM_MEMORYRESPONSE_H
