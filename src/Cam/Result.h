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

#ifndef CAMREM_RESULT_H
#define CAMREM_RESULT_H

#include <memory>
#include "../json/src/json.hpp"

using json = nlohmann::json;
using std::shared_ptr;
using std::vector;

namespace Cam {
    class Result {
    private:
        json data_;
        shared_ptr<vector<char>> imagedata_;
    public:
        Result();
        Result(json data);
        Result(shared_ptr<vector<char>> image);
        json getData();
        shared_ptr<vector<char>> getImage();
    };
}

#endif //CAMREM_RESULT_H
