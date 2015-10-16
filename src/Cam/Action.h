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

#ifndef CAMREM_ACTION_H
#define CAMREM_ACTION_H
#include <functional>
#include <condition_variable>
#include <memory>
#include "Result.h"

using std::function;
using std::condition_variable;
using std::mutex;
using std::unique_lock;
using std::shared_ptr;
using std::lock_guard;

namespace Cam {
    class Action {
    private:
        bool processed_;
        condition_variable processed_cv_;
        mutex processed_mutex_;
        function<shared_ptr<Result>()> callback_;
        shared_ptr<Result> result_;
    public:
        Action(function<shared_ptr<Result>()> callback);
        void process();
        shared_ptr<Result> getResult();
    };
}

#endif //CAMREM_ACTION_H
