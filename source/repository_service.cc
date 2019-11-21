#include "repository_service.h"

#include <vector>

#include "inventory_updater.h"
#include "inventory_visitor.h"
#include "location.h"

namespace inventory {

namespace {

struct InventoryItem {
  const ItemType type;
  Amount amount;
  Price price;
};

#define FOR_EACH(objects, action) \
  for (auto& it : objects) {      \
    action(it);                   \
  }

#define FIND_ONE_DO(objects, pred, action) \
  do {                                     \
    for (auto& it : objects) {             \
      if (pred(it)) {                      \
        action(it);                        \
        return;                            \
      }                                    \
    }                                      \
  } while (0)

struct ReposImpl {
  ReposImpl(Location location, std::initializer_list<InventoryItem> items) : location(location), items(items) {
  }

  void accept(InventoryVisitor& visitor, const ItemType request_item) const {
    FIND_ONE_DO(items,
                [&](auto& it) { return it.type == request_item; },
                [&](auto& it) { visitor.visit(location, it.type, it.amount, it.price); });
  }

  void accept(InventoryUpdater& visitor, const ItemType request_item) {
    FIND_ONE_DO(items,
                [&](auto& it) { return it.type == request_item; },
                [&](auto& it) { visitor.visit(location, it.type, &it.amount, it.price); });
  }

private:
  Location location;
  std::vector<InventoryItem> items;
};

struct AllRepositories {
  static std::vector<ReposImpl> init() {
    return {{Brazil, {{iPod, 100, 65}, {iPhone, 100, 100}}}, {Argentina, {{iPod, 100, 100}, {iPhone, 50, 150}}}};
  }

  static void reset() {
    repos() = init();
  }

  static std::vector<ReposImpl>& repos() {
    static std::vector<ReposImpl> repositories;  // = init();
    return repositories;
  }
};

}  // namespace

void RepositoryService::accept(InventoryVisitor& visitor, const ItemType type) const {
  FOR_EACH(AllRepositories::repos(), [&](auto& it) { it.accept(visitor, type); });
}

void RepositoryService::accept(InventoryUpdater& visitor, const ItemType type) {
  FOR_EACH(AllRepositories::repos(), [&](auto& it) { it.accept(visitor, type); });
}

void RepositoryService::reset() {
  AllRepositories::reset();
}

}  // namespace inventory
