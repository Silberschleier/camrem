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

#include "Bindings.h"

bool ::Http::Bindings::jsonNotFound(Request *request) {
    shared_ptr<Response> response = make_shared<Response>();
    response->content = make_shared<string>("{ \"message\": \"Not Found\" }");
    request->response = response;
    request->response->status = STATUS_NOTFOUND;
    return true;
}

bool ::Http::Bindings::staticFile(Request *request, string filename, unsigned int status) {
    shared_ptr<FileResponse> response = make_shared<FileResponse>(filename);
    request->response = response;
    request->response->status = status;
    return true;
}

bool ::Http::Bindings::dummyAction(Request *request, Cam::CamHandler *cam) {
    auto action = cam->dummy();
    cam->enqueue(action);
    auto res = action->getResult();

    shared_ptr<Response> response = make_shared<Response>();
    if ( res ) {
        response->content = make_shared<string>(res->getData().dump());
    } else {
        BOOST_LOG_TRIVIAL(error) << "Faulty result";
        return false;
    }

    response->status = STATUS_OK;

    request->response = response;

    return true;
}
