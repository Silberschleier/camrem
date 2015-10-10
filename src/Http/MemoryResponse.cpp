//
// Created by Christopher Schmidt on 10.10.15.
//

#include "MemoryResponse.h"

bool Http::MemoryResponse::is_static() {
    return false;
}

string *Http::MemoryResponse::getContent() {
    return &content;
}
