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

#include "CamFacade.h"

Cam::CamFacade::CamFacade() { }

Cam::CamFacade::~CamFacade() { }

Cam::CamFacade *Cam::CamFacade::getInstance() {
    static CamFacade instance;
    return &instance;
}

shared_ptr<Cam::Result> Cam::CamFacade::dummy() {
    auto callback = bind(&CamHandler::sleep, &camera_);
    auto action = make_shared<Action>(callback);

    camera_.enqueue(action);

    return action->getResult();
}

shared_ptr<Cam::Result> Cam::CamFacade::getPreview() {
    auto callback = bind(&CamHandler::getPreview, &camera_);
    auto action = make_shared<Action>(callback);

    camera_.enqueue(action);

    return action->getResult();
}

shared_ptr<Cam::Result> Cam::CamFacade::getConfig() {
    auto callback = bind(&CamHandler::getConfig, &camera_);
    auto action = make_shared<Action>(callback);

    camera_.enqueue(action);
    return action->getResult();
}
