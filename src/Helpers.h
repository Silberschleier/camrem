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

#ifndef CAMREM_HELPERS_H
#define CAMREM_HELPERS_H

#include <fstream>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/formatter_parser.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

namespace expr = boost::log::expressions;
using std::string;
using std::shared_ptr;
using std::make_shared;

/*
 * Initializes Boost log.
 */
void init_logging();

/*
 * Loads a file into a string.
 * @param The path to the file
 * @return Pointer to a string containing the contents of the file, or NULL if an error occurs.
 */
shared_ptr<string> load_file(string path);

/*
 * Called on SIGINT. Simply exits the program.
 * Tidy up work and the stopping of other processes should go into here.
 */
void signal_handler(int sig);

#endif //CAMREM_HELPERS_H
