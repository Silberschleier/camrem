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

#include "Result.h"


Cam::Result::Result() { }

Cam::Result::Result(json data) : data_(data) { }

Cam::Result::Result(shared_ptr<vector<char>> image) : imagedata_(image) { }

json Cam::Result::getData() {
    return data_;
}

shared_ptr<vector<char>> Cam::Result::getImage() {
    return imagedata_;
}
