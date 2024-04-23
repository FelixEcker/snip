#include "LogHelper.hpp"
#include "SnipStore.hpp"

#include <format>
#include <iostream>
#include <vector>

void help() {
  std::cerr << "usage: snip [store <file> <name> | show <name> | get <name> [as]]\n";
  std::cerr << "\n";
  std::cerr << "commands:\n";
  std::cerr << "  store <file> <name>  Stores the given file with the given name\n";
  std::cerr << "  show <name>          Show the given snip with the user's PAGER\n";
  std::cerr << "  get <name> [as]      Gets the snips contents. If as is not set,\n\
                       it is simply put into stdout. If as is set,\n\
                       it will be put in a new file of the same name.\n";
}

int do_store(Snip::SnipStore store, std::vector<std::string> args) {
  if (args.size() != 2) {
    Snip::LogHelper::error("snip store: expecting 2 arguments: file, name");
    Snip::LogHelper::error("See snip --help for further information");
    return 1;
  }

  return store.store(args[0], args[1]) ? 0 : 1;
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

  Snip::LogHelper::error(std::format("unknown command \"{}\"!", COMMAND));
  return 1;
}
