//
// Created by Christopher Schmidt on 10.10.15.
//

#include "Bindings.h"

bool ::Http::Bindings::jsonNotFound(Http::Request *request) {
    MemoryResponse *response = new MemoryResponse();
    response->content = "{ \"message\": \"Not Found\" }";
    request->response = response;
    request->response->status = 404;
    return true;
}

bool ::Http::Bindings::staticFile(Request *request, string filename) {
    FileResponse *response = new FileResponse("html/404.html");
    request->response = response;
    request->response->status = 404;
    return true;
}
