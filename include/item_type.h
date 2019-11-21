#ifndef INVENTORY_ITEM_TYPE_H
#define INVENTORY_ITEM_TYPE_H

#include <string>
#include <vector>

namespace inventory {

enum ItemType { iPod = 0, iPhone = 1, UnknownItem = 2 };

inline std::vector<ItemType> getAllItemTypes() {
  return {iPod, iPhone};
}

ItemType itemTypeFromString(const std::string&);

}  // namespace inventory

#endif
