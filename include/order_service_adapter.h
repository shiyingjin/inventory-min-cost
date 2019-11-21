#ifndef INVENTORY_ORDER_SERVICE_ADAPTER_H
#define INVENTORY_ORDER_SERVICE_ADAPTER_H

#include "order_service.h"
#include "repository_service.h"

#include <string>

namespace inventory {

struct Order;

struct OrderServiceAdapter : OrderService, RepositoryService {
  std::string fulfill(const std::string&);

  static OrderServiceAdapter& instance();

private:
  OrderServiceAdapter() = default;
  RepositoryService& getRepos() override;
};

#define Store() OrderServiceAdapter::instance()

}  // namespace inventory

#endif
