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

#ifndef CAMREM_GPWRAPPER_H
#define CAMREM_GPWRAPPER_H

#include <gphoto2/gphoto2.h>
#include "../Helpers.h"
#include "../easylogging/src/easylogging++.h"

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
            GPhotoAbilitiesList(GPContext *context);
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

            int count();
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

        class GPhotoCameraFile {
        private:
            bool ok_;
            CameraFile *camerafile_;
        public:
            GPhotoCameraFile();
            ~GPhotoCameraFile();
            bool is_valid();
            operator CameraFile *();
        };
    }
}




#endif //CAMREM_GPWRAPPER_H
