//
// Created by Christopher Schmidt on 10.10.15.
//

#include "FileResponse.h"

bool Http::FileResponse::is_static() {
    return true;
}

shared_ptr<string> Http::FileResponse::getContent() {
    if ( not content ) {
        content = load_file(filename_);
    }

    return content;
}

Http::FileResponse::FileResponse(string file) {
    filename_ = file;
}
