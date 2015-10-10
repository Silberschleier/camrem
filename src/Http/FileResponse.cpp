//
// Created by Christopher Schmidt on 10.10.15.
//

#include "FileResponse.h"

bool Http::FileResponse::is_static() {
    return true;
}

string *Http::FileResponse::getContent() {
    if ( NULL == content_ ) {
        content_ = load_file(filename_);
    }

    return content_;
}

Http::FileResponse::FileResponse(string file) {
    filename_ = file;
    content_ = NULL;
}
