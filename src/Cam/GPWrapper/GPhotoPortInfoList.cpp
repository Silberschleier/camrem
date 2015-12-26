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

#include "GPhotoPortInfoList.h"

Cam::GPWrapper::GPhotoPortInfoList::GPhotoPortInfoList() {
    int ret = gp_port_info_list_new( &portinfoList_ );
    ok_ = ( GP_OK == ret);
    if ( not ok_ ) {
        LOG(WARNING) << "gp_port_info_list_new: " << gp_result_as_string(ret);
    }

    // Fill portinfo_list
    ret = gp_port_info_list_load( portinfoList_ );
    ok_ = ( GP_OK == ret);
    if ( not ok_ ) {
        LOG(WARNING) << "gp_port_info_list_load: " << gp_result_as_string(ret);
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

int Cam::GPWrapper::GPhotoPortInfoList::count() {
    int ret = gp_port_info_list_count( portinfoList_ );
    if ( 0 > ret ) {
        LOG(WARNING) << "gp_port_info_list_count: " << ret;
    }

    return ret;
}