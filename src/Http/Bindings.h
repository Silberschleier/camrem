//
// Created by Christopher Schmidt on 10.10.15.
//

#ifndef CAMREM_APIBINDINGS_H
#define CAMREM_APIBINDINGS_H

#include <memory>
#include "Request.h"
#include "Response.h"
#include "FileResponse.h"

using std::shared_ptr;
using std::make_shared;

namespace Http {
    namespace Bindings {
        bool jsonNotFound(Request *request);
        bool staticFile(Request *request, string filename, unsigned int status);
    }
}


#endif //CAMREM_APIBINDINGS_H
