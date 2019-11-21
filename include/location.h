#ifndef INVENTORY_LOCATION_H
#define INVENTORY_LOCATION_H

#include <string>

namespace inventory {

enum Location { Brazil, Argentina, Unknown };

Location locationFromString(const std::string&);

}  // namespace inventory

#endif
