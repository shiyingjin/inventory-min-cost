#ifndef INVENTORY_ORDER_SERVICE_H
#define INVENTORY_ORDER_SERVICE_H

#include "order_status.h"

namespace inventory {

struct Order;
struct RepositoryService;

struct OrderService {
  virtual ~OrderService() = default;

  OrderStatus fulfill(const Order&);

private:
  virtual RepositoryService& getRepos() = 0;
};

}  // namespace inventory

#endif
