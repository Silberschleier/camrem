//
// Created by Christopher Schmidt on 13.10.15.
//

#ifndef CAMREM_CAMERA_H
#define CAMREM_CAMERA_H

#include <thread>
#include <gphoto2/gphoto2.h>
#include "GPWrapper.h"
#include "../Helpers.h"

using std::thread;

namespace Cam {
    class Cam {
    private:
        thread thread_;
        GPWrapper::GPhotoContext context_;
        GPWrapper::GPhotoCamera camera_;

        bool init_camera();
        void handle_events();
    public:
        Cam();
    };
}

#endif //CAMREM_CAMERA_H
