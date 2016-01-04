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
    context_ = unique_ptr<GPWrapper::GPhotoContext>(new GPWrapper::GPhotoContext);
    abilities_list_ = unique_ptr<GPWrapper::GPhotoAbilitiesList>(new GPWrapper::GPhotoAbilitiesList(*context_));

    thread_ = thread( &CamHandler::handle_events, this );
}

bool Cam::CamHandler::init() {
    GPWrapper::GPhotoCameraList camera_list;


    // OSX Workaround
    // TODO: Look for something more elegant
#ifdef __APPLE__
    system("killall PTPCamera 2> /dev/null");
    std::this_thread::sleep_for(std::chrono::seconds(1));
#endif

    camera_ = unique_ptr<GPWrapper::GPhotoCamera>(new GPWrapper::GPhotoCamera());

    if (   not camera_list.is_valid()
        || not portinfo_list_.is_valid()
        || not abilities_list_->is_valid()
        || not camera_->is_valid()
        || portinfo_list_.count() < 0 ) {
        return false;
    }

    int ret;

    // Detect connected cameras
    ret = gp_abilities_list_detect(*abilities_list_, portinfo_list_, camera_list, *context_ );
    if ( GP_OK != ret ) {
        LOG(WARNING) << "gp_abilities_list_detect: " << gp_result_as_string(ret);
        return false;
    }

    // Check if any camera is available
    ret = gp_list_count( camera_list );
    if ( ret < 1 ) {
        LOG_N_TIMES(1, INFO) << "No Cameras found. Retrying silently...";
        return false;
    }

    // Init camera
    ret = gp_camera_init( *camera_, *context_ );
    if ( GP_OK != ret ) {
        LOG(WARNING) << "gp_camera_init: " << gp_result_as_string(ret);
        return false;
    }

    LOG(TRACE) << "gp_camera_init successful";
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
        action = action_queue_.front();
        action_queue_.pop();
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
            LOG(WARNING) << "gp_camera_wait_for_event: " << gp_result_as_string(ret);

            // Wait for successful reinit
            reinit();
            continue;
        }

        switch (event_type) {
            case GP_EVENT_CAPTURE_COMPLETE:
                LOG(TRACE) << "GP_EVENT_CAPTURE_COMPLETE";
                break;
            case GP_EVENT_FILE_ADDED:
                LOG(TRACE) << "GP_EVENT_FILE_ADDED";
                break;
            case GP_EVENT_FOLDER_ADDED:
                LOG(TRACE) << "GP_EVENT_FOLDER_ADDED";
                break;
            case GP_EVENT_TIMEOUT:
                process_action();
                break;
            case GP_EVENT_UNKNOWN:
                LOG(TRACE) << "GP_EVENT_UNKNOWN, event_data: " << (char *) event_data;
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
        LOG(WARNING) << "gp_camera_capture_preview: " << gp_result_as_string(ret);
        // TODO: Return error result
    }

    // Download the preview
    ret = gp_file_get_data_and_size(file, &image_data, &image_size);
    if ( GP_OK != ret ) {
        LOG(WARNING) << "gp_file_get_data_and_size: " << gp_result_as_string(ret);
        // TODO: Return error result
    }

    // Store the data
    shared_ptr<vector<char>> data = make_shared<vector<char>>(image_data, image_data + image_size);

    return make_shared<Result>(data);
}

shared_ptr<Cam::Result> Cam::CamHandler::getConfig() {
    GPWrapper::GPhotoCameraWidget widget;

    int ret = gp_camera_get_config(*camera_, widget, *context_);
    if ( GP_OK != ret ) {
        LOG(WARNING) << "gp_camera_get_config: " << gp_result_as_string(ret);
        // TODO: Return error result
    }

    return make_shared<Result>(widget.getData());
}

shared_ptr<Cam::Result> Cam::CamHandler::setConfig(string path, json data) {
    GPWrapper::GPhotoCameraWidget widget;

    int ret = gp_camera_get_config(*camera_, widget, *context_);
    if ( GP_OK != ret ) {
        LOG(WARNING) << "gp_camera_get_config: " << gp_result_as_string(ret);
        // TODO: Return error result
    }

    auto child = widget.getChildByPath(path);
    if ( not child ) {
        // TODO: Error handling
        return NULL;
    }

    if ( data["value"].is_boolean() ) {
        child->setValue(data["value"].get<bool>());
    } else if ( data["value"].is_string() ) {
        child->setValue(data["value"].get<string>());
    } else if ( data["value"].is_number() ) {
        child->setValue(data["value"].get<float>());
    } else {
        // TODO: Error handling
        return NULL;
    }

    ret = gp_camera_set_config(*camera_, widget, *context_);
    if ( GP_OK != ret ) {
        LOG(WARNING) << "gp_camera_set_config: " << gp_result_as_string(ret);
        // TODO: Return error result
    }

    return make_shared<Result>(child->getData());
}
