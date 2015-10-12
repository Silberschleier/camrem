//
// Created by Christopher Schmidt on 10.10.15.
//

#include "Bindings.h"

bool ::Http::Bindings::jsonNotFound(Http::Request *request) {
    shared_ptr<Response> response = make_shared<Response>();
    response->content = make_shared<string>("{ \"message\": \"Not Found\" }");
    request->response = response;
    request->response->status = 404;
    return true;
}

bool ::Http::Bindings::staticFile(Request *request, string filename) {
    shared_ptr<FileResponse> response = make_shared<FileResponse>(filename);
    request->response = response;
    request->response->status = 404;
    return true;
}
