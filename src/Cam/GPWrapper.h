//
// Created by Christopher Schmidt on 14.10.15.
//

#ifndef CAMREM_GPWRAPPER_H
#define CAMREM_GPWRAPPER_H

#include <gphoto2/gphoto2.h>
#include "../Helpers.h"

namespace Cam {
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

        class GPhotoCamera {
        private:
            bool ok_;
            Camera *camera_;
        public:
            GPhotoCamera();
            ~GPhotoCamera();
            bool is_valid();
            operator Camera *();
        };

        class GPhotoContext {
        private:
            bool ok_;
            GPContext *context_;
        public:
            GPhotoContext();
            ~GPhotoContext();
            bool is_valid();
            operator GPContext *();
        };
    }
}




#endif //CAMREM_GPWRAPPER_H
