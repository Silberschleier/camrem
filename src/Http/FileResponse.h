/*
    Copyright (C) 2015  Christopher Schmidt

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef CAMREM_FILERESPONSE_H
#define CAMREM_FILERESPONSE_H

#include "Response.h"
#include "../Helpers.h"

namespace Http {
    class FileResponse : public Response {
    private:
        string filename_;
    public:
        FileResponse(string file);
        shared_ptr<string> getContent();
        bool is_static();
    };
}



#endif //CAMREM_FILERESPONSE_H
