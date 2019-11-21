#include "order_service.h"

#include <algorithm>
#include <unordered_map>
#include <vector>

#include "cost_calculator.h"
#include "inventory_updater.h"
#include "inventory_visitor.h"
#include "order.h"
#include "order_visitor.h"
#include "repository_service.h"

namespace inventory {

namespace {

struct Fulfilling : OrderVisitor {
  Fulfilling(RepositoryService& repos) : repos(repos), filled(true) {
  }

  bool operator()(const Order& order) {
    order.accept(*this);
    return filled;
  }

private:
  void visit(const ItemType item_type, const Amount amount) override {
    struct ItemTotalInventory : InventoryVisitor {
      void visit(Location, ItemType, Amount item_amount, Price) override {
        amount += item_amount;
      }
      Amount amount = 0;
    } total;
    repos.accept(total, item_type);
    filled = filled && total.amount >= amount;
  }
  RepositoryService& repos;
  bool filled;
};

struct CalculateImpl : InventoryUpdater {
  CalculateImpl(RepositoryService& repos, const Order& order, ItemType item_type, Amount order_amount)
      : repos(repos),
        item_type(item_type),
        request_amount(order_amount),
        cost_caculator(order.where(), order.customer()) {
  }

  Price operator()() {
    repos.accept(*this, item_type);
    return calc();
  }

private:
  using Unit = Amount;
  const std::vector<Unit> units = {CostCalculator::transportUnit(), 1};

  struct InventoryStat {
    Location inventory_location = Unknown;
    Price price = 0;
    Amount* inventory_amount = nullptr;
    std::unordered_map<Unit, Price> unit_cost;
  };

  Price calc() {
    auto rest = request_amount;
    for (auto& unit : units) {
      rest = calcInUnit(rest, unit);
    }
    return total_price;
  }

  Amount calcInUnit(Amount rest, Amount unit) {
    std::sort(statistics.begin(), statistics.end(), [=](const InventoryStat& a, const InventoryStat& b) {
      return a.unit_cost.at(unit) < b.unit_cost.at(unit);
    });

    for (auto& it : statistics) {
      if (rest < unit)
        break;
      Amount fill_count = std::min(rest, *it.inventory_amount);
      fill_count -= fill_count % unit;
      *(it.inventory_amount) -= fill_count;
      total_price += cost_caculator.totalCost(it.inventory_location, it.price, fill_count);
      rest -= fill_count;
    }
    return rest;
  }

  void visit(Location location, const ItemType, Amount* amount, Price price) override {
    InventoryStat stat;
    stat.inventory_amount = amount;
    stat.inventory_location = location;
    stat.price = price;

    auto rest_count = request_amount;
    for (auto& unit : units) {
      auto count = rest_count - rest_count % unit;
      stat.unit_cost[unit] = cost_caculator.unitCost(location, price, count);
      rest_count %= unit;
    }
    statistics.push_back(stat);
  }

  RepositoryService& repos;
  ItemType item_type;
  Amount request_amount;
  CostCalculator cost_caculator;
  Price total_price = 0;
  std::vector<InventoryStat> statistics;
};

struct TotalPrice : OrderVisitor {
  TotalPrice(RepositoryService& repos, const Order& order) : repos(repos), order(order), total(0) {
  }

  Price operator()() {
    order.accept(*this);
    return total;
  }

private:
  void visit(const ItemType item_type, const Amount amount) override {
    CalculateImpl impl(repos, order, item_type, amount);
    total += impl();
  }

  RepositoryService& repos;
  const Order& order;
  Price total;
};

}  // namespace

OrderStatus OrderService::fulfill(const Order& order) {
  auto& repos = getRepos();
  repos.reset();
  return Fulfilling(repos)(order) ? TotalPrice(repos, order)() : OUT_OF_STOCK;
}

}  // namespace inventory
