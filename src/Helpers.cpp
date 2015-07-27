//
// Created by Christopher Schmidt on 27.07.15.
//

#include "Helpers.h"

void init_logging() {
    boost::log::add_file_log(
            boost::log::keywords::file_name = "camrem_%N.log",
            boost::log::keywords::format = (
                    expr::stream
                    << "[" << boost::log::trivial::severity
                    << "]\t" << expr::smessage
            )
    );

    boost::log::add_console_log(
            std::cout,
            boost::log::keywords::format = (
                    expr::stream
                    << "[" << boost::log::trivial::severity
                    << "]\t" << expr::smessage
            )
    );

    boost::log::core::get()->set_filter(
            boost::log::trivial::severity >= boost::log::trivial::info
    );
}

void signal_handler(int sig) {
    BOOST_LOG_TRIVIAL(info) << "Recieved SIGINT (Ctrl+C). Terminating...";
    exit(1);
}
