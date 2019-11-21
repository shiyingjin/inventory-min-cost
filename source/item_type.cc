#include "item_type.h"

#include <unordered_map>

namespace inventory {

ItemType itemTypeFromString(const std::string& str) {
  static std::unordered_map<std::string, ItemType> mapping{{"IPOD", iPod}, {"IPHONE", iPhone}};
  auto it = mapping.find(str);
  return it != mapping.end() ? it->second : UnknownItem;
}

}  // namespace inventory
