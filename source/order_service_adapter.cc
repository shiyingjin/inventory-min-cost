#include "order_service_adapter.h"

#include <regex>
#include <sstream>

#include "customer_info.h"
#include "inventory_visitor.h"
#include "order.h"
#include "order_service.h"
#include "repository_service.h"

namespace inventory {

namespace {

struct InventoryPrinter : InventoryVisitor {
  InventoryPrinter(RepositoryService& repos, std::ostream& os) : repos(repos), os(os) {
  }

  void print() {
    auto item_types = getAllItemTypes();
    for (auto& type : item_types)
      repos.accept(*this, type);
  }

private:
  void visit(Location, ItemType, Amount inventory, unsigned int) override {
    os << ":" << inventory;
  }

  RepositoryService& repos;
  std::ostream& os;
};

bool validOrder(const std::string& order_str) {
  static std::regex reg("^(BRAZIL|ARGENTINA)((:[0-9|A-Z]{12,13})?)(:(IPOD|IPHONE):\\d+){1,2}$");
  return std::regex_match(order_str, reg);
}

}  // namespace

std::string OrderServiceAdapter::fulfill(const std::string& order_str) {
  if (!validOrder(order_str))
    return "INVALID ORDER";

  Order order = Order::fromString(order_str);
  auto result = OrderService::fulfill(order);
  std::ostringstream oss;
  oss << result;

  InventoryPrinter printer(getRepos(), oss);
  printer.print();
  return oss.str();
}

OrderServiceAdapter& OrderServiceAdapter::instance() {
  static OrderServiceAdapter adapter;
  return adapter;
}

RepositoryService& OrderServiceAdapter::getRepos() {
  return static_cast<RepositoryService&>(*this);
}

}  // namespace inventory
