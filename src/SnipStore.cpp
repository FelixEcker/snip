#include "SnipStore.hpp"

#include "LogHelper.hpp"

#include <algorithm>
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

/* class SnipStore */

SnipStore::SnipStore() {
  /* get snipstore directory and create if not exists */
  char *snip_store_env = std::getenv("SNIP_STORE");
  this->location = resolve_path(
      snip_store_env != NULL ? snip_store_env : SNIP_STORE_DEFAULT
    );

  if (this->location.back() != '/') {
    this->location += '/';
  }
  
  LogHelper::debug("snipstore @ " + this->location);

  if (access(this->location.c_str(), F_OK) == -1) {
    LogHelper::debug("creating snip_store directory");
    std::filesystem::create_directories(this->location);
  }

  /* get a list of all snips present in the store */
  const std::filesystem::path snipstore{this->location};
  std::ranges::for_each(
    std::filesystem::directory_iterator{snipstore},
    [&, this](const auto& dir_entry) {
      if (!dir_entry.is_regular_file()) {
        return;
      }

      const std::string path = dir_entry.path().filename();
      this->snips.insert(path);
      LogHelper::debug(std::format("found snip \"{}\"", path));
    }
  );
}

bool SnipStore::store(std::string file, std::string name) {
  if (access(file.c_str(), F_OK) == -1) {
    LogHelper::error("provided file does not exist!");
    return false;
  }

  if (this->snips.find(name) != this->snips.end()) {
    LogHelper::error("snip with given name already exists!");
    return false;
  }

  std::filesystem::copy(file, this->location + name);

  return true;
}

std::string SnipStore::get_location() {
  return this->location;
}

} /* namespace Snip::SnipStore */
