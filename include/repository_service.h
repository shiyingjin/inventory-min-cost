#ifndef INVENTORY_REPOSITORY_SERVICE_H
#define INVENTORY_REPOSITORY_SERVICE_H

#include "item_type.h"

namespace inventory {

struct InventoryVisitor;
struct InventoryUpdater;

struct RepositoryService {
  virtual ~RepositoryService() = default;

  void accept(InventoryVisitor&, const ItemType) const;
  void accept(InventoryUpdater&, const ItemType);

  void reset();
};

}  // namespace inventory

#endif
