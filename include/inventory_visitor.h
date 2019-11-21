#ifndef INENTORY_INVENTORY_VISITOR_H
#define INENTORY_INVENTORY_VISITOR_H

#include "amount.h"
#include "item_type.h"
#include "location.h"
#include "price.h"

namespace inventory {

struct InventoryVisitor {
  virtual ~InventoryVisitor() = default;
  virtual void visit(Location, ItemType, Amount, Price) = 0;
};

}  // namespace inventory

#endif
