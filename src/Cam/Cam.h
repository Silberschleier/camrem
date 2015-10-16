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

#ifndef CAMREM_CAMERA_H
#define CAMREM_CAMERA_H

#include <thread>
#include <queue>
#include <mutex>
#include <gphoto2/gphoto2.h>
#include "GPWrapper.h"
#include "../Helpers.h"
#include "../ConfigHandler.h"
#include "Action.h"

using std::thread;
using std::priority_queue;
using std::unique_ptr;
using std::shared_ptr;
using std::mutex;


namespace Cam {
    class Cam {
    private:
        thread thread_;
        mutex queue_lock_;
        priority_queue<shared_ptr<Action>> action_queue_;
        unique_ptr<GPWrapper::GPhotoContext> context_;
        unique_ptr<GPWrapper::GPhotoCamera> camera_;

        bool init();
        bool reinit();
        void enqueue(shared_ptr<Action> action);
        void handle_events();
    public:
        Cam();

    };
}

#endif //CAMREM_CAMERA_H
