#include "order.h"

#include <sstream>
#include <vector>

#include "order_visitor.h"

namespace inventory {

namespace {

template <char delimiter>
struct WordDelimitedBy : std::string {};

std::vector<std::string> split(const std::string& s, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream token_stream(s);
  while (std::getline(token_stream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

}  // namespace

Order::Order(Location location, std::initializer_list<std::pair<ItemType, Amount>> items)
    : location(location), customer_info(), items(items) {
}

Order::Order(Location country, const std::string& passport_id, std::initializer_list<std::pair<ItemType, Amount>> items)
    : location(country), customer_info(passport_id), items(items) {
}

void Order::accept(OrderVisitor& visitor) const {
  for (auto& it : items)
    visitor.visit(it.first, it.second);
}

Location Order::where() const {
  return location;
}

const CustomerInfo& Order::customer() const {
  return customer_info;
}

// input format: <purchase_country>:<optional_passport_number>:<item_type>:<number_of_
// units_to_be_ordered>:<item_type>:<number_of_units_to_be_ordered>
Order Order::fromString(const std::string& order_str) {
  auto results = split(order_str, ':');
  Location order_location = locationFromString(results[0]);
  std::string passport;
  size_t item_index = 1;
  bool has_passport = results.size() % 2 == 0;
  if (has_passport) {
    passport = results[1];
    item_index++;
  }
  Order order(order_location, passport, {});
  for (; item_index < results.size(); item_index += 2) {
    order.items.push_back({itemTypeFromString(results[item_index]), std::stoi(results[item_index + 1])});
  }
  return order;
}

}  // namespace inventory
