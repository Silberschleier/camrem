//
// Created by Christopher Schmidt on 10.10.15.
//

#ifndef CAMREM_APIBINDINGS_H
#define CAMREM_APIBINDINGS_H

#include "Request.h"
#include "Response.h"
#include "MemoryResponse.h"
#include "FileResponse.h"

namespace Http {
    namespace ApiBindings {
        bool jsonNotFound(Request *request);
        bool staticFile(Request *request, string filename);
    }
}


#endif //CAMREM_APIBINDINGS_H
