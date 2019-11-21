#include "location.h"

#include <unordered_map>

namespace inventory {

Location locationFromString(const std::string& location_str) {
  static std::unordered_map<std::string, Location> mapping{{"BRAZIL", Brazil}, {"ARGENTINA", Argentina}};
  auto it = mapping.find(location_str);
  return it != mapping.end() ? it->second : Unknown;
}

}  // namespace inventory
