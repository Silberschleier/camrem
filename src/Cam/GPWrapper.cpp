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

#include "GPWrapper.h"

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

Cam::GPWrapper::GPhotoAbilitiesList::GPhotoAbilitiesList() {
    int ret = gp_abilities_list_new( &abilitiesList_ );
    ok_ = ( GP_OK == ret);
    if ( not ok_ ) {
        LOG(WARNING) << "gp_abilities_list_new: " << gp_result_as_string(ret);
    }
}

Cam::GPWrapper::GPhotoAbilitiesList::~GPhotoAbilitiesList() {
    gp_abilities_list_free( abilitiesList_ );
}

bool Cam::GPWrapper::GPhotoAbilitiesList::is_valid() {
    return ok_;
}

Cam::GPWrapper::GPhotoAbilitiesList::operator CameraAbilitiesList *() {
    return abilitiesList_;
}

Cam::GPWrapper::GPhotoPortInfoList::GPhotoPortInfoList() {
    int ret = gp_port_info_list_new( &portinfoList_ );
    ok_ = ( GP_OK == ret);
    if ( not ok_ ) {
        LOG(WARNING) << "gp_port_info_list_new: " << gp_result_as_string(ret);
    }
}

Cam::GPWrapper::GPhotoPortInfoList::~GPhotoPortInfoList() {
    gp_port_info_list_free( portinfoList_ );
}

Cam::GPWrapper::GPhotoPortInfoList::operator GPPortInfoList *() {
    return portinfoList_;
}

bool Cam::GPWrapper::GPhotoPortInfoList::is_valid() {
    return ok_;
}

Cam::GPWrapper::GPhotoCamera::GPhotoCamera() {
    int ret = gp_camera_new( &camera_ );
    ok_ = ( GP_OK == ret);
    if ( not ok_ ) {
        LOG(WARNING) << "gp_camera_new: " << gp_result_as_string(ret);
    }
}

Cam::GPWrapper::GPhotoCamera::~GPhotoCamera() {
    gp_camera_unref( camera_ );
}

bool Cam::GPWrapper::GPhotoCamera::is_valid() {
    return ok_;
}

Cam::GPWrapper::GPhotoCamera::operator Camera *() {
    return camera_;
}

Cam::GPWrapper::GPhotoContext::GPhotoContext() {
    context_ = gp_context_new();
    ok_ = true;
}

Cam::GPWrapper::GPhotoContext::~GPhotoContext() {
    gp_context_unref( context_ );
}

bool Cam::GPWrapper::GPhotoContext::is_valid() {
    return ok_;
}

Cam::GPWrapper::GPhotoContext::operator GPContext *() {
    return context_;
}

Cam::GPWrapper::GPhotoCameraFile::GPhotoCameraFile() {
    int ret = gp_file_new(&camerafile_);
    ok_ = ( GP_OK == ret );
    if ( not ok_ ) {
        LOG(WARNING) << "gp_file_new: " << gp_result_as_string(ret);
    }
}

Cam::GPWrapper::GPhotoCameraFile::~GPhotoCameraFile() {
    gp_file_unref(camerafile_);
}

bool Cam::GPWrapper::GPhotoCameraFile::is_valid() {
    return ok_;
}

Cam::GPWrapper::GPhotoCameraFile::operator CameraFile *() {
    return camerafile_;
}
