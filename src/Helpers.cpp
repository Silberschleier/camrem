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

#include "Helpers.h"

void init_logging() {
    boost::log::add_common_attributes();
    boost::log::add_file_log(
            boost::log::keywords::file_name = "camrem_%N.log",
            boost::log::keywords::format = (
                    expr::stream
                    << "[" << expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")
                    << "] [" << boost::log::trivial::severity
                    << "]\t" << expr::smessage
            )
    );

    boost::log::add_console_log(
            std::cout,
            boost::log::keywords::format = (
                    expr::stream
                    << "[" << expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")
                    << "] [" << boost::log::trivial::severity
                    << "]\t" << expr::smessage
            )
    );

    boost::log::core::get()->set_filter(
            boost::log::trivial::severity >= boost::log::trivial::trace
    );
}

void signal_handler(int sig) {
    BOOST_LOG_TRIVIAL(info) << "Recieved SIGINT (Ctrl+C). Terminating...";
    exit(1);
}

shared_ptr<string> load_file(string path) {
    // TODO: Rethink if this is really safe
    BOOST_LOG_TRIVIAL(trace) << "Reading file '" << path << "'...";

    std::ifstream file;
    file.open(path);

    if (not file.is_open() ) {
        BOOST_LOG_TRIVIAL(error) << "Could not open file '" << path << "'.";
        return NULL;
    }

    auto str = make_shared<string>(  (std::istreambuf_iterator<char>(file)),
                                std::istreambuf_iterator<char>());

    return str;
}
