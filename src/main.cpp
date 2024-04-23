#include "LogHelper.hpp"

#include <cstdlib>
#include <format>
#include <iostream>
#include <string>

#define SNIP_STORE_DEFAULT "~/.snip_store/"

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

int main(void) {
  char *snip_store_env = std::getenv("SNIP_STORE");
  std::string snip_store = snip_store_env != NULL ? snip_store_env : SNIP_STORE_DEFAULT;
  snip_store = resolve_path(snip_store);

  Snip::LogHelper::debug(std::format("snipstore @ {}", snip_store));

  return 0;
}
