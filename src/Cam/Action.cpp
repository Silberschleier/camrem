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

#include "Action.h"


Cam::Action::Action(function<shared_ptr<Result>()> callback) {
    callback_ = callback;
}

void Cam::Action::process() {
    result_ = callback_();

    // Notify threads waiting for the result
    {
        lock_guard<mutex> lock(processed_mutex_);
        processed_ = true;
        processed_cv_.notify_all();
    }
}

shared_ptr<Cam::Result> Cam::Action::getResult() {
    // Wait till processing is finished
    unique_lock<mutex> lock(processed_mutex_);

    // Check for spurious wake-ups
    while ( not processed_ ) {
        processed_cv_.wait(lock);
    }

    return result_;
}

