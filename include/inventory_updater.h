#ifndef INVENTORY_INVENTORY_UPDATER_H
#define INVENTORY_INVENTORY_UPDATER_H

#include "amount.h"
#include "item_type.h"
#include "location.h"
#include "price.h"

namespace inventory {

struct InventoryUpdater {
  virtual ~InventoryUpdater() = default;
  virtual void visit(Location, ItemType, Amount*, Price) = 0;
};

}  // namespace inventory

#endif
