#include "SnipStore.hpp"

#include "LogHelper.hpp"

#include <filesystem>
#include <format>
#include <unistd.h>

namespace Snip {

std::string resolve_path(std::string org_path) {
  if (org_path.length() == 0) {
    return org_path;
  }

  if (!org_path.starts_with("~/")) {
    return org_path;
  }

  const std::string HOME_DIR = std::getenv("HOME");
  org_path.erase(0, 1); /* get rid of tilde */

  return HOME_DIR + org_path;
}

SnipStore::SnipStore() {
  char *snip_store_env = std::getenv("SNIP_STORE");
  this->location = resolve_path(
      snip_store_env != NULL ? snip_store_env : SNIP_STORE_DEFAULT
    );
  
  LogHelper::debug("snipstore @ " + this->location);

  if (access(this->location.c_str(), F_OK) == -1) {
    LogHelper::debug("creating snip_store directory");
    std::filesystem::create_directories(this->location);
  }
}

std::string SnipStore::get_location() {
  return this->location;
}

} /* namespace Snip::SnipStore */
