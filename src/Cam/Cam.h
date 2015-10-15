//
// Created by Christopher Schmidt on 13.10.15.
//

#ifndef CAMREM_CAMERA_H
#define CAMREM_CAMERA_H

#include <thread>
#include <gphoto2/gphoto2.h>
#include "GPWrapper.h"
#include "../Helpers.h"
#include "../ConfigHandler.h"

using std::thread;
using std::unique_ptr;

namespace Cam {
    class Cam {
    private:
        thread thread_;
        unique_ptr<GPWrapper::GPhotoContext> context_;
        unique_ptr<GPWrapper::GPhotoCamera> camera_;

        bool init();
        bool reinit();
        void handle_events();
    public:
        Cam();
    };
}

#endif //CAMREM_CAMERA_H
