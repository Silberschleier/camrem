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

#ifndef CAMREM_GPHOTOCAMERAWIDGET_H
#define CAMREM_GPHOTOCAMERAWIDGET_H

#include "../GPWrapper.h"
#include "../../json/src/json.hpp"

using std::string;
using std::vector;
using nlohmann::json;

namespace Cam {
    namespace GPWrapper {
        class GPhotoCameraWidget {
        private:
            CameraWidget *widget_ = NULL;

            json getDataText();
            json getDataRange();
            json getDataToggle();
            json getDataDate();
            json getDataRadio();
        public:
            ~GPhotoCameraWidget();
            operator CameraWidget *();
            operator CameraWidget **();

            string getLabel();
            string getName();
            CameraWidgetType getType();
            vector<shared_ptr<GPhotoCameraWidget>> getChilds();
            json getData();
            int countChildren();

        };
    }
}


#endif //CAMREM_GPHOTOCAMERAWIDGET_H
