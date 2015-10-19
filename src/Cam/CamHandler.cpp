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

#include "CamHandler.h"


Cam::CamHandler::CamHandler() {
    thread_ = thread( &CamHandler::handle_events, this );
}

bool Cam::CamHandler::init() {
    GPWrapper::GPhotoCameraList camera_list;
    GPWrapper::GPhotoPortInfoList portinfo_list;
    GPWrapper::GPhotoAbilitiesList abilities_list;

    // OSX Workaround
    // TODO: Look for something more elegant
#ifdef __APPLE__
    system("killall PTPCamera");
    std::this_thread::sleep_for(std::chrono::seconds(1));
#endif

    camera_ = unique_ptr<GPWrapper::GPhotoCamera>(new GPWrapper::GPhotoCamera());
    context_ = unique_ptr<GPWrapper::GPhotoContext>(new GPWrapper::GPhotoContext());

    if ( not camera_list.is_valid() || not portinfo_list.is_valid() || not abilities_list.is_valid() || not camera_->is_valid() ) {
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


    ret = gp_abilities_list_load( abilities_list, *context_ );
    if ( GP_OK != ret ) {
        BOOST_LOG_TRIVIAL(warning) << "gp_abilities_list_load: " << gp_result_as_string(ret);
        return false;
    }

    // Detect connected cameras
    ret = gp_abilities_list_detect( abilities_list, portinfo_list, camera_list, *context_ );
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
    ret = gp_camera_init( *camera_, *context_ );
    if ( GP_OK != ret ) {
        BOOST_LOG_TRIVIAL(warning) << "gp_camera_init: " << gp_result_as_string(ret);
        return false;
    }

    BOOST_LOG_TRIVIAL(trace) << "gp_camera_init successful";
    return true;
}

bool Cam::CamHandler::reinit() {
    gp_camera_exit(*camera_, *context_);
    while ( not init() );
    return true;
}

void Cam::CamHandler::enqueue(shared_ptr<Action> action) {
    queue_lock_.lock();
    action_queue_.push(action);
    queue_lock_.unlock();
}

void Cam::CamHandler::process_action() {
    shared_ptr<Action> action;
    queue_lock_.lock();

    if ( not action_queue_.empty() ) {
        action = action_queue_.top();
        action_queue_.pop();
    } else {
        BOOST_LOG_TRIVIAL(trace) << "Action queue empty";
    }

    queue_lock_.unlock();

    if ( action ) {
        action->process();
    }
}

void Cam::CamHandler::handle_events() {
    int poll_timeout = ConfigHandler::getInstance()->config["Camera"]["EventPollTimeout"];
    int ret;
    CameraEventType event_type;
    void *event_data;

    // Wait for successful initialization
    while ( not this->init() );

    for(;;) {
        ret = gp_camera_wait_for_event(*camera_, poll_timeout, &event_type, &event_data, *context_);
        if ( GP_OK != ret ) {
            BOOST_LOG_TRIVIAL(warning) << "gp_camera_wait_for_event: " << gp_result_as_string(ret);

            // Wait for successful reinit
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
                process_action();
                break;
            case GP_EVENT_UNKNOWN:
                BOOST_LOG_TRIVIAL(trace) << "GP_EVENT_UNKNOWN, event_data: " << (char *) event_data;
                break;
        }

        free (event_data);

    }
}


shared_ptr<Cam::Result> Cam::CamHandler::sleep() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    json data = {{"sleep", "test"}};
    return std::make_shared<Result>(data);
}

shared_ptr<Cam::Result> Cam::CamHandler::getPreview() {
    GPWrapper::GPhotoCameraFile file;
    const char *image_data;
    unsigned long image_size;
    int ret;

    // Capture the preview
    ret = gp_camera_capture_preview(*camera_, file, *context_);
    if ( GP_OK != ret ) {
        BOOST_LOG_TRIVIAL(warning) << "gp_camera_capture_preview: " << gp_result_as_string(ret);
        // TODO: Return error result
    }

    // Download the preview
    ret = gp_file_get_data_and_size(file, &image_data, &image_size);
    if ( GP_OK != ret ) {
        BOOST_LOG_TRIVIAL(warning) << "gp_file_get_data_and_size: " << gp_result_as_string(ret);
        // TODO: Return error result
    }

    // Store the data
    shared_ptr<vector<char>> data = make_shared<vector<char>>(image_data, image_data + image_size);

    return make_shared<Result>(data);
}
