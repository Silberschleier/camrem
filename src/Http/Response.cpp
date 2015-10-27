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

#include "Response.h"

Http::Response::Response() {

}

Http::Response::~Response() {

}

bool Http::Response::is_static() {
    return false;
}

const char *Http::Response::getRawData() {
    return content_->data();
}

unsigned long Http::Response::getRawDataSize() {
    return content_->size();
}

void Http::Response::setContent(shared_ptr<string> data) {
    content_ = make_shared<vector<char>>(data->begin(), data->end());
}

void Http::Response::setContent(string data) {
    content_ = make_shared<vector<char>>(data.begin(), data.end());
}

void Http::Response::setContent(const char *data, unsigned long size) {
    content_ = make_shared<vector<char>>(data, data + size);
}

void Http::Response::setContent(shared_ptr<vector<char>> data) {
    content_ = data;
}

