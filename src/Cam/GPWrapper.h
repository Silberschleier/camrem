//
// Created by Christopher Schmidt on 14.10.15.
//

#ifndef CAMREM_GPWRAPPER_H
#define CAMREM_GPWRAPPER_H

#include <gphoto2/gphoto2.h>
#include "../Helpers.h"

namespace GPWrapper {
    class GPhotoCameraList {
    private:
        bool ok_;
        CameraList *cameraList_;
    public:
        GPhotoCameraList();
        ~GPhotoCameraList();
        bool is_valid();
        operator CameraList *();
    };

    class GPhotoAbilitiesList {
    private:
        bool ok_;
        CameraAbilitiesList *abilitiesList_;
    public:
        GPhotoAbilitiesList();
        ~GPhotoAbilitiesList();
        bool is_valid();
        operator CameraAbilitiesList *();
    };

    class GPhotoPortInfoList {
    private:
        bool ok_;
        GPPortInfoList *portinfoList_;
    public:
        GPhotoPortInfoList();
        ~GPhotoPortInfoList();
        bool is_valid();
        operator GPPortInfoList *();
    };
}


#endif //CAMREM_GPWRAPPER_H
