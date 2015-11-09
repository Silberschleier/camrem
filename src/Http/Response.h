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

#ifndef CAMREM_RESPONSE_H
#define CAMREM_RESPONSE_H

#include <string>
#include <vector>
#include <memory>
#include "../easylogging/src/easylogging++.h"

using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;

namespace Http {
    class Response {
    private:
        shared_ptr<vector<char>> content_;
    public:
        unsigned int status;

        Response();
        ~Response();

        const char * getRawData();
        unsigned long getRawDataSize();
        void setContent(shared_ptr<string> data);
        void setContent(string data);
        void setContent(const char *data, unsigned long size);
        void setContent(shared_ptr<vector<char>> data);

        /*
         * @return Always false.
         */
        virtual bool is_static();
    };
}



#endif //CAMREM_RESPONSE_H
