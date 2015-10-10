//
// Created by Christopher Schmidt on 10.10.15.
//

#include "ApiBindings.h"

bool ::Http::ApiBindings::emptyResponse(Http::Request *request) {
    request->response = new Response();
    return true;
}
