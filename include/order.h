#ifndef INVENTORY_ORDER_H
#define INVENTORY_ORDER_H

#include "amount.h"
#include "customer_info.h"
#include "item_type.h"
#include "location.h"

#include <initializer_list>
#include <utility>
#include <vector>

namespace inventory {

struct OrderVisitor;

struct Order {
  Order(Location, std::initializer_list<std::pair<ItemType, Amount>>);
  Order(Location, const std::string&, std::initializer_list<std::pair<ItemType, Amount>>);

  void accept(OrderVisitor&) const;

  Location where() const;
  const CustomerInfo& customer() const;

  static Order fromString(const std::string&);

private:
  Location location;
  CustomerInfo customer_info;
  std::vector<std::pair<ItemType, Amount>> items;
};

}  // namespace inventory

#endif
