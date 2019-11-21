#ifndef INVENTORY_ORDER_STATUS_H
#define INVENTORY_ORDER_STATUS_H

#include "price.h"

#include <ostream>

namespace inventory {

struct OrderStatus {
  OrderStatus(Price price);

  static const OrderStatus& outOfStock();
  friend std::ostream& operator<<(std::ostream&, const OrderStatus&);
  friend bool operator==(const OrderStatus&, const OrderStatus&);
  friend bool operator!=(const OrderStatus&, const OrderStatus&);

private:
  OrderStatus();

  bool filled;
  Price price;
};

#define OUT_OF_STOCK OrderStatus::outOfStock()

}  // namespace inventory

#endif
