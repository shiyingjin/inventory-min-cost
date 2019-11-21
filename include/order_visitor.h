#ifndef INVENTORY_ORDER_VISITOR_H
#define INVENTORY_ORDER_VISITOR_H

#include "amount.h"
#include "item_type.h"

namespace inventory {

struct CustomerInfo;

struct OrderVisitor {
  virtual ~OrderVisitor() = default;

  virtual void visit(const ItemType, const Amount) = 0;
};

}  // namespace inventory

#endif
