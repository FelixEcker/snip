#ifndef SNIP_SNIP_STORE_HPP
#define SNIP_SNIP_STORE_HPP

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

    std::string get_location();
  private:
    std::string location;
};

} /* namespace Snip */

#endif /* #ifndef SNIP_SNIP_STORE_HPP */
