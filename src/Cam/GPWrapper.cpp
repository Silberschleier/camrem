//
// Created by Christopher Schmidt on 14.10.15.
//

#include "GPWrapper.h"

GPWrapper::GPhotoCameraList::GPhotoCameraList() {
    int ret = gp_list_new( &cameraList_ );
    ok_  = ( GP_OK == ret);
    if ( not ok_ ) {
        BOOST_LOG_TRIVIAL(warning) << "gp_list_new: " << gp_result_as_string(ret);
    }
}

GPWrapper::GPhotoCameraList::~GPhotoCameraList() {
    gp_list_unref( cameraList_ );
}

bool GPWrapper::GPhotoCameraList::is_valid() {
    return ok_;
}

GPWrapper::GPhotoCameraList::operator CameraList *() {
    return cameraList_;
}

GPWrapper::GPhotoAbilitiesList::GPhotoAbilitiesList() {
    int ret = gp_abilities_list_new( &abilitiesList_ );
    ok_ = ( GP_OK == ret);
    if ( not ok_ ) {
        BOOST_LOG_TRIVIAL(warning) << "gp_abilities_list_new: " << gp_result_as_string(ret);
    }
}

GPWrapper::GPhotoAbilitiesList::~GPhotoAbilitiesList() {
    gp_abilities_list_free( abilitiesList_ );
}

bool GPWrapper::GPhotoAbilitiesList::is_valid() {
    return ok_;
}

GPWrapper::GPhotoAbilitiesList::operator CameraAbilitiesList *() {
    return abilitiesList_;
}

GPWrapper::GPhotoPortInfoList::GPhotoPortInfoList() {
    int ret = gp_port_info_list_new( &portinfoList_ );
    ok_ = ( GP_OK == ret);
    if ( not ok_ ) {
        BOOST_LOG_TRIVIAL(warning) << "gp_port_info_list_new: " << gp_result_as_string(ret);
    }
}

GPWrapper::GPhotoPortInfoList::~GPhotoPortInfoList() {
    gp_port_info_list_free( portinfoList_ );
}

GPWrapper::GPhotoPortInfoList::operator GPPortInfoList *() {
    return portinfoList_;
}

bool GPWrapper::GPhotoPortInfoList::is_valid() {
    return ok_;
}

GPWrapper::GPhotoCamera::GPhotoCamera() {
    int ret = gp_camera_new( &camera_ );
    ok_ = ( GP_OK == ret);
    if ( not ok_ ) {
        BOOST_LOG_TRIVIAL(warning) << "gp_camera_new: " << gp_result_as_string(ret);
    }
}

GPWrapper::GPhotoCamera::~GPhotoCamera() {
    gp_camera_unref( camera_ );
}

bool GPWrapper::GPhotoCamera::is_valid() {
    return ok_;
}

GPWrapper::GPhotoCamera::operator Camera *() {
    return camera_;
}

GPWrapper::GPhotoContext::GPhotoContext() {
    context_ = gp_context_new();
    ok_ = true;
}

GPWrapper::GPhotoContext::~GPhotoContext() {
    gp_context_unref( context_ );
}

bool GPWrapper::GPhotoContext::is_valid() {
    return ok_;
}

GPWrapper::GPhotoContext::operator GPContext *() {
    return context_;
}
