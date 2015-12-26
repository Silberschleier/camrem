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

#include "GPhotoCameraList.h"

Cam::GPWrapper::GPhotoCameraList::GPhotoCameraList() {
    int ret = gp_list_new( &cameraList_ );
    ok_  = ( GP_OK == ret);
    if ( not ok_ ) {
        LOG(WARNING) << "gp_list_new: " << gp_result_as_string(ret);
    }
}

Cam::GPWrapper::GPhotoCameraList::~GPhotoCameraList() {
    gp_list_unref( cameraList_ );
}

bool Cam::GPWrapper::GPhotoCameraList::is_valid() {
    return ok_;
}

Cam::GPWrapper::GPhotoCameraList::operator CameraList *() {
    return cameraList_;
}