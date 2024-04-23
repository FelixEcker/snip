#ifndef SNIP_SNIP_STORE_HPP
#define SNIP_SNIP_STORE_HPP

#include <set>
#include <string>

namespace Snip {

const std::string SNIP_STORE_DEFAULT = 
#ifndef __SNIP_DEBUG
  "~/.snip_store/"
#else
  "./snip_store/"
#endif
  ;

class SnipStore {
  public:
    SnipStore();

    bool store(std::string file, std::string name);

    std::string get_snip_path(std::string name);

    std::string get_location();
  private:
    std::string location;

    std::set<std::string> snips;
};

} /* namespace Snip */

#endif /* #ifndef SNIP_SNIP_STORE_HPP */
