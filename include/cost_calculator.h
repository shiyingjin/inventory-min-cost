#ifndef INVNETORY_COST_CALCULATOR_H
#define INVNETORY_COST_CALCULATOR_H

#include "amount.h"
#include "price.h"
#include "location.h"

namespace inventory {

struct CustomerInfo;

struct CostCalculator {
  CostCalculator(Location order_location, const CustomerInfo& customer);

  Price totalCost(Location source, Price price, Amount amount) const ;
  Price unitCost(Location source, Price price, Amount amount) const;

  static Amount transportUnit();

private:
  Location order_location;
  const CustomerInfo& customer;
};

}

#endif
