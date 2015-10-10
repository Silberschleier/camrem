//
// Created by Christopher Schmidt on 10.10.15.
//

#ifndef CAMREM_FILERESPONSE_H
#define CAMREM_FILERESPONSE_H

#include "Response.h"
#include "../Helpers.h"

namespace Http {
    class FileResponse : public Response {
    private:
        string filename_;
        string *content_;
    public:
        FileResponse(string file);
        string *getContent();
        bool is_static();
    };
}



#endif //CAMREM_FILERESPONSE_H
