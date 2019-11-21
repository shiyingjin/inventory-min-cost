#include "cost_calculator.h"

#include "customer_info.h"

namespace inventory {

namespace {

const Amount TRANSPORT_UNIT = 10;
const Amount TRANSPORT_UNIT_COST = 400;
const Amount LOCAL_DISCOUNT = 20;  // percent

unsigned int my_div(unsigned int dividend, unsigned int divisor) {
  return dividend % divisor == 0 ? dividend / divisor : dividend / divisor + 1;
}

unsigned int discount(const CustomerInfo& customer, Location country) {
  return customer.isFrom(country) ? LOCAL_DISCOUNT : 0;  // percent
}

Price transportCost(const CustomerInfo& customer, Location source, Amount amount) {
  return my_div(amount, TRANSPORT_UNIT) * TRANSPORT_UNIT_COST * (100 - discount(customer, source)) / 100;
}

}  // namespace

CostCalculator::CostCalculator(Location order_location, const CustomerInfo& customer)
    : order_location(order_location), customer(customer) {
}

Price CostCalculator::totalCost(Location source, Price price, Amount amount) const {
  auto cost = price * amount;
  return source == order_location ? cost : cost + transportCost(customer, source, amount);
}

Price CostCalculator::unitCost(Location source, Price price, Amount amount) const {
  return amount == 0 ? 0 : totalCost(source, price, amount) / amount;
}

Amount CostCalculator::transportUnit() {
  return TRANSPORT_UNIT;
}

}  // namespace inventory
