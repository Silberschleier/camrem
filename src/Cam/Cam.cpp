//
// Created by Christopher Schmidt on 13.10.15.
//

#include "Cam.h"


Cam::Cam::Cam() {
    thread_ = thread( &Cam::handle_events, this );
}

bool Cam::Cam::init() {
    GPWrapper::GPhotoCameraList camera_list;
    GPWrapper::GPhotoPortInfoList portinfo_list;
    GPWrapper::GPhotoAbilitiesList abilities_list;

    if ( not camera_list.is_valid() || not portinfo_list.is_valid() || not abilities_list.is_valid() || not camera_.is_valid() ) {
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

bool Cam::Cam::reinit() {
    gp_camera_exit(camera_, context_);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return init();
}


void Cam::Cam::handle_events() {
    int poll_timeout = ConfigHandler::getInstance()->config["Camera"]["EventPollTimeout"];
    int ret;
    CameraEventType event_type;
    void *event_data;


    this->init();

    for(;;) {
        ret = gp_camera_wait_for_event(camera_, poll_timeout, &event_type, &event_data, context_);
        if ( GP_OK != ret ) {
            BOOST_LOG_TRIVIAL(warning) << "gp_camera_wait_for_event: " << gp_result_as_string(ret);
            reinit();
            continue;
        }

        switch (event_type) {
            case GP_EVENT_CAPTURE_COMPLETE:
                BOOST_LOG_TRIVIAL(trace) << "GP_EVENT_CAPTURE_COMPLETE";
                break;
            case GP_EVENT_FILE_ADDED:
                BOOST_LOG_TRIVIAL(trace) << "GP_EVENT_FILE_ADDED";
                break;
            case GP_EVENT_FOLDER_ADDED:
                BOOST_LOG_TRIVIAL(trace) << "GP_EVENT_FOLDER_ADDED";
                break;
            case GP_EVENT_TIMEOUT:
                BOOST_LOG_TRIVIAL(trace) << "GP_EVENT_TIMEOUT";
                break;
            case GP_EVENT_UNKNOWN:
                BOOST_LOG_TRIVIAL(trace) << "GP_EVENT_UNKNOWN, event_data: " << (char *) event_data;
                break;
        }

        free (event_data);

    }
}
