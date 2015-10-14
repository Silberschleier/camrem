//
// Created by Christopher Schmidt on 13.10.15.
//

#include "Cam.h"

Cam::Cam::Cam() {
    thread_ = thread( &Cam::handle_events, this );
}

bool Cam::Cam::init_camera() {
    GPWrapper::GPhotoCameraList camera_list;
    GPWrapper::GPhotoPortInfoList portinfo_list;
    GPWrapper::GPhotoAbilitiesList abilities_list;

    if ( not camera_list.is_valid() || not portinfo_list.is_valid() || not abilities_list.is_valid() || camera_.is_valid() ) {
        return false;
    }

    int ret;

    // Fill portinfo_list
    ret = gp_port_info_list_load( portinfo_list );
    if ( GP_OK != ret ) {
        BOOST_LOG_TRIVIAL(warning) << "gp_port_info_list_load: " << gp_result_as_string(ret);
        return false;
    }

    ret = gp_port_info_list_count( portinfo_list );
    if ( 0 > ret ) {
        BOOST_LOG_TRIVIAL(warning) << "gp_port_info_list_count: " << ret;
        return false;
    }


    ret = gp_abilities_list_load( abilities_list, context_ );
    if ( GP_OK != ret ) {
        BOOST_LOG_TRIVIAL(warning) << "gp_abilities_list_load: " << gp_result_as_string(ret);
        return false;
    }

    // Detect connected cameras
    ret = gp_abilities_list_detect( abilities_list, portinfo_list, camera_list, context_ );
    if ( GP_OK != ret ) {
        BOOST_LOG_TRIVIAL(warning) << "gp_abilities_list_detect: " << gp_result_as_string(ret);
        return false;
    }

    // Check if any camera is available
    ret = gp_list_count( camera_list );
    if ( ret < 1 ) {
        BOOST_LOG_TRIVIAL(warning) << "gp_list_count: " << ret;
        return false;
    }

    // Init camera
    ret = gp_camera_init( camera_, context_ );
    if ( GP_OK != ret ) {
        BOOST_LOG_TRIVIAL(warning) << "gp_camera_init: " << gp_result_as_string(ret);
        return false;
    }

    return true;
}

void Cam::Cam::handle_events() {
    BOOST_LOG_TRIVIAL(info) << "Handling events for camera...";
    this->init_camera();
}
