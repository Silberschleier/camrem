//
// Created by Christopher Schmidt on 27.07.15.
//

#ifndef CAMREM_HELPERS_H
#define CAMREM_HELPERS_H

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

/*
 * Initializes Boost log.
 */
void init_logging();
/*
 * Called on SIGINT. Simply exits the program.
 * Tidy up work and the stopping of other processes should go into here.
 */
void signal_handler(int sig);

#endif //CAMREM_HELPERS_H
