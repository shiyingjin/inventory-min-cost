#include "order_status.h"

namespace inventory {

OrderStatus::OrderStatus() : filled(false), price(0) {
}

OrderStatus::OrderStatus(Price price) : filled(true), price(price) {
}

const OrderStatus& OrderStatus::outOfStock() {
  static OrderStatus out_of_stock;
  return out_of_stock;
}

std::ostream& operator<<(std::ostream& os, const OrderStatus& obj) {
  if (obj.filled) {
    os << obj.price;
  } else {
    os << "OUT_OF_STOCK";
  }
  return os;
}

bool operator==(const OrderStatus& lhs, const OrderStatus& rhs) {
  return lhs.filled == rhs.filled && lhs.price == rhs.price;
}

bool operator!=(const OrderStatus& lhs, const OrderStatus& rhs) {
  return !(lhs == rhs);
}

}  // namespace inventory
