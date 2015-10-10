//
// Created by Christopher Schmidt on 09.10.15.
//

#include "Response.h"

Http::Response::Response() {
    content_ = "hallo";
    status_ = 200;
}

Http::Response::~Response() {

}
