#include "LogHelper.hpp"

#include <iostream>

namespace Snip::LogHelper {

void _log(int level, std::string message) {
  switch (level) {
  case 0:
#ifdef __SNIP_DEBUG
    std::cerr << "[DEBUG]    " << message << "\n";
#endif
    return;
  case 1:
    std::cerr << "[WARN]     ";
    break;
  case 2:
    std::cerr << "[ERROR]    ";
    break;
  case 3:
    std::cerr << "[CRITICAL] ";
    break;
  }

  std::cerr << message << "\n";
}

void debug(std::string message) {
  _log(0, message);
}

void warn(std::string message) {
  _log(1, message);
}

void error(std::string message) {
  _log(2, message);
}

void critical(std::string message) {
  _log(3, message);
}

} /* namespace Snip::LogHelper */
