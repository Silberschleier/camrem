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

#ifndef CAMREM_GPHOTOPORTINFOLIST_H
#define CAMREM_GPHOTOPORTINFOLIST_H

#include "../GPWrapper.h"

namespace Cam{
    namespace GPWrapper{
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
    }
}


#endif //CAMREM_GPHOTOPORTINFOLIST_H
