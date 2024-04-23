#include "LogHelper.hpp"
#include "SnipStore.hpp"

#include <errno.h>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <vector>

void help() {
  std::cerr << "usage: snip [store <file> <name> | rm <name> | show <name> | get <name> [as] | list]\n";
  std::cerr << "\n";
  std::cerr << "commands:\n";
  std::cerr << "  store <file> <name>  Stores the given file with the given name\n";
  std::cerr << "  rm <name>            Removes the snip\n";
  std::cerr << "  show <name>          Show the given snip with the user's SNIP_PAGER\n";
  std::cerr << "  get <name> [as]      Gets the snips contents. If as is not set,\n\
                       it is simply put into stdout. If as is set,\n\
                       it will be put in a new file of the same name.\n";
  std::cerr << "  list                 List all stored snips\n";
}

int do_store(Snip::SnipStore store, std::vector<std::string> args) {
  if (args.size() != 2) {
    Snip::LogHelper::error("snip store: expecting 2 arguments: file, name");
    Snip::LogHelper::error("See snip --help for further information");
    return 1;
  }

  return store.store(args[0], args[1]) ? 0 : 1;
}

int do_show(Snip::SnipStore store, std::vector<std::string> args) {
  if (args.size() != 1) {
    Snip::LogHelper::error("snip show: expecting 1 arguments: name");
    Snip::LogHelper::error("See snip --help for further information");
    return 1;
  }

  std::string snip_path = store.get_snip_path(args[0]);
  if (snip_path.empty()) {
    Snip::LogHelper::error("no such snip!");
    return 1;
  }

  Snip::LogHelper::debug(std::format("Showing snip @ \"{}\"!", snip_path));

  char *env_snip_pager = std::getenv("SNIP_PAGER");
  
  /* ensure that we really have a pager with this one */
  env_snip_pager = env_snip_pager != NULL ? env_snip_pager : std::getenv("PAGER");
  
  std::string snip_pager = env_snip_pager != NULL ? env_snip_pager : "more";
  std::string full_cmd = std::format("{} {}", snip_pager, snip_path);

  return system(full_cmd.data());
}

int do_get(Snip::SnipStore store, std::vector<std::string> args) {
  if (args.size() == 0 || args.size() > 2) {
    Snip::LogHelper::error("snip show: expecting 1 arguments: name OR 2 arguments: name as");
    Snip::LogHelper::error("See snip --help for further information");
    return 1;
  }

  std::string snip_path = store.get_snip_path(args[0]);
  if (snip_path.empty()) {
    Snip::LogHelper::error("no such snip!");
    return 1;
  }

  if (args.size() == 2) {
    std::filesystem::copy(snip_path, args[1]);
    return 0;
  }

  std::ifstream cont(snip_path);

  if (cont.is_open()) {
    std::cout << cont.rdbuf();
    return 0;
  }

  Snip::LogHelper::critical(std::format("couldn't open file \"{}\" for reading!",
                                        snip_path));
  return 1;
}

int do_rm(Snip::SnipStore store, std::vector<std::string> args) {
  if (args.size() != 1) {
    Snip::LogHelper::error("snip rm: expecting 1 arguments: name");
    Snip::LogHelper::error("See snip --help for further information");
    return 1;
  }

  std::string snip_path = store.get_snip_path(args[0]);
  if (snip_path.empty()) {
    Snip::LogHelper::error("no such snip!");
    return 1;
  }

  std::remove(snip_path.c_str());
  return 0;
}

int main(int argc, char **argv) {
  std::vector<std::string> args(argv, argv+argc);
  if (args.size() == 1 || (args.size() > 1 && args[1] == "--help")) {
    help();
    return 0;
  }

  const std::string COMMAND = args[1];
  args.erase(args.begin(), args.begin() + 2);

  Snip::SnipStore snip_store;

  if (COMMAND == "store") {
    return do_store(snip_store, args);
  }
  if (COMMAND == "show") {
    return do_show(snip_store, args);
  }
  if (COMMAND == "get") {
    return do_get(snip_store, args);
  }
  if (COMMAND == "rm") {
    return do_rm(snip_store, args);
  }
  if (COMMAND == "list") {
    for (const std::string &snip : snip_store.get_snips()) {
      std::cout << snip << "\n";
    }
    return 0;
  }

  Snip::LogHelper::error(std::format("unknown command \"{}\"!", COMMAND));
  return 1;
}
