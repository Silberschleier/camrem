//
// Created by Christopher Schmidt on 27.07.15.
//

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
