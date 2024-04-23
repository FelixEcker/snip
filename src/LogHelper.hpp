#ifndef LOG_HELPER_HPP
#define LOG_HELPER_HPP

#include <string>

namespace Snip::LogHelper {

void debug(std::string message);
void warn(std::string message);
void error(std::string message);
void critical(std::string message);

} /* namespace Snip::LogHelper */

#endif /* #ifndef LOG_HELPER_HPP */
