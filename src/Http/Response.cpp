//
// Created by Christopher Schmidt on 09.10.15.
//

#include "Response.h"

Http::Response::Response() {

}

Http::Response::~Response() {

}

bool Http::Response::is_static() {
    return false;
}

shared_ptr<string> Http::Response::getContent() {
    return content;
}
