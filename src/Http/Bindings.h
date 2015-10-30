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

#ifndef CAMREM_APIBINDINGS_H
#define CAMREM_APIBINDINGS_H

#include <memory>
#include "Request.h"
#include "Response.h"
#include "Http.h"
#include "../Cam/CamHandler.h"
#include "../Cam/CamFacade.h"

using std::shared_ptr;
using std::make_shared;

namespace Http {
    class Request;

    namespace Bindings {
        /*
         * Responds with an API error and response code STATUS_NOTFOUND
         * @param request to process.
         * @return Always true.
         */
        bool jsonNotFound(Request *request);

        /*
         * Responds with a static response and given response code.
         */
        bool staticFile(Request *request, string filename, unsigned int status);

        bool getPreview(Request *request);

        // TODO: Remove this.
        bool dummyAction(Request *request);
    }
}


#endif //CAMREM_APIBINDINGS_H
