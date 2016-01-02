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

#include "GPhotoCameraWidget.h"

Cam::GPWrapper::GPhotoCameraWidget::~GPhotoCameraWidget() {
    if ( NULL != widget_ ) {
//        gp_widget_free(widget_);
    }
}

Cam::GPWrapper::GPhotoCameraWidget::operator CameraWidget *() {
    return widget_;
}

Cam::GPWrapper::GPhotoCameraWidget::operator CameraWidget **() {
    return &widget_;
}

string Cam::GPWrapper::GPhotoCameraWidget::getLabel() {
    if ( NULL == widget_ ) {
        LOG(TRACE) << "CameraWidget is nullpointer";
        return "";
    }

    const char *label;

    int ret = gp_widget_get_label(widget_, &label);
    if ( GP_OK != ret ) {
        LOG(WARNING) << "gp_widget_get_label: " << gp_result_as_string(ret);
        return "";
    }

    return string(label);
}

string Cam::GPWrapper::GPhotoCameraWidget::getName() {
    if ( NULL == widget_ ) {
        LOG(TRACE) << "CameraWidget is nullpointer";
        return "";
    }

    const char *name;

    int ret = gp_widget_get_name(widget_, &name);
    if ( GP_OK != ret ) {
        LOG(WARNING) << "gp_widget_get_name: " << gp_result_as_string(ret);
        return "";
    }

    return string(name);
}

CameraWidgetType Cam::GPWrapper::GPhotoCameraWidget::getType() {
    if ( NULL == widget_ ) {
        LOG(TRACE) << "CameraWidget is nullpointer";
        return (CameraWidgetType) GP_ERROR;
    }

    CameraWidgetType type;

    int ret = gp_widget_get_type(widget_, &type);
    if ( GP_OK != ret ) {
        LOG(WARNING) << "gp_widget_get_type: " << gp_result_as_string(ret);
        return (CameraWidgetType) GP_ERROR;
    }

    return type;
}

json Cam::GPWrapper::GPhotoCameraWidget::getData() {
    json data;
    switch ( getType() ) {
        case GP_WIDGET_WINDOW:break;
        case GP_WIDGET_SECTION:break;
        case GP_WIDGET_BUTTON:break;
        case GP_WIDGET_TEXT:
            data = getDataText();
            break;
        case GP_WIDGET_RANGE:
            data = getDataRange();
            break;
        case GP_WIDGET_TOGGLE:
            data = getDataToggle();
            break;
        case GP_WIDGET_MENU:
        case GP_WIDGET_RADIO:
            data = getDataRadio();
            break;
        case GP_WIDGET_DATE:
            data = getDataDate();
            break;
    }

    data["label"] = getLabel();
    data["name"] = getName();

    json child_data;
    for ( auto child : getChilds() ) {
        child_data.push_back(child->getData());
    }

    data["children"] = child_data;

    return data;
}

int Cam::GPWrapper::GPhotoCameraWidget::countChildren() {
    if ( NULL == widget_ ) {
        return 0;
    }

    return gp_widget_count_children(widget_);
}


vector<shared_ptr<Cam::GPWrapper::GPhotoCameraWidget>> Cam::GPWrapper::GPhotoCameraWidget::getChilds() {
    int num_childs = countChildren();
    shared_ptr<GPhotoCameraWidget> temp;
    vector<shared_ptr<GPhotoCameraWidget>> list;


    for ( int i = 0; i < num_childs; i++ ) {
        temp = make_shared<GPhotoCameraWidget>();

        int ret = gp_widget_get_child(widget_, i, *temp);
        if( GP_OK != ret ) {
            LOG(WARNING) << "gp_widget_get_child: " << gp_result_as_string(ret);
            continue;
        }

        list.push_back(temp);
    }

    return list;
}

json Cam::GPWrapper::GPhotoCameraWidget::getDataText() {
    if ( getType() != GP_WIDGET_TEXT ) {
        LOG(ERROR) << "GPWrapper::GPhotoCameraWidget::getDataText(): Widget is not of type TEXT";
        return "{}"_json;
    }

    char *value;
    int ret = gp_widget_get_value(widget_, &value);
    if ( GP_OK != ret ) {
        LOG(ERROR) << "gp_widget_get_value: " << gp_result_as_string(ret);
        return "{}"_json;
    }

    json data;
    data["type"] = "text";
    data["value"] = value;

    return data;
}

json Cam::GPWrapper::GPhotoCameraWidget::getDataRange() {
    if ( getType() != GP_WIDGET_RANGE ) {
        LOG(ERROR) << "GPWrapper::GPhotoCameraWidget::getDataRange(): Widget is not of type RANGE";
        return "{}"_json;
    }

    float value, min, max, step;

    int ret = gp_widget_get_range(widget_, &min, &max, &step);
    if ( GP_OK != ret ) {
        LOG(ERROR) << "gp_widget_get_range: " << gp_result_as_string(ret);
        return "{}"_json;
    }

    ret = gp_widget_get_value(widget_, &value);
    if ( GP_OK != ret ) {
        LOG(ERROR) << "gp_widget_get_value: " << gp_result_as_string(ret);
        return "{}"_json;
    }

    json data;
    data["type"] = "range";
    data["value"] = value;
    data["min"] = min;
    data["max"] = max;
    data["step"] = step;

    return data;
}

json Cam::GPWrapper::GPhotoCameraWidget::getDataToggle() {
    if ( getType() != GP_WIDGET_TOGGLE ) {
        LOG(ERROR) << "GPWrapper::GPhotoCameraWidget::getDataToggle(): Widget is not of type TOGGLE";
        return "{}"_json;
    }

    int ret, value;
    ret = gp_widget_get_value(widget_, &value);
    if ( GP_OK != ret ) {
        LOG(ERROR) << "gp_widget_get_value: " << gp_result_as_string(ret);
        return "{}"_json;
    }

    json data;
    data["type"] = "toggle";
    data["value"] = value == 1;

    return data;
}

json Cam::GPWrapper::GPhotoCameraWidget::getDataDate() {
    return "{}"_json;
}

json Cam::GPWrapper::GPhotoCameraWidget::getDataRadio() {
    CameraWidgetType type = getType();
    if ( type != GP_WIDGET_RADIO && type != GP_WIDGET_MENU ) {
        LOG(ERROR) << "GPWrapper::GPhotoCameraWidget::getDataToggle(): Widget is not of type RADIO or MENU";
        return "{}"_json;
    }

    int count, ret;
    char *value;

    ret = gp_widget_get_value(widget_, &value);
    if ( GP_OK != ret ) {
        LOG(ERROR) << "gp_widget_get_value: " << gp_result_as_string(ret);
        return "{}"_json;
    }

    count = gp_widget_count_choices(widget_);

    json data;
    data["value"] = value;

    for (int i = 0; i < count; i++) {
        const char *choice;

        ret = gp_widget_get_choice(widget_, i, &choice);
        if ( GP_OK != ret ) {
            LOG(ERROR) << "gp_widget_get_choice: " << gp_result_as_string(ret);
            continue;
        }

        data["choices"].push_back(choice);
    }

    return data;
}
