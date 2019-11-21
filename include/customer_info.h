#ifndef INVENTORY_PASSPORT_INFO_H
#define INVENTORY_PASSPORT_INFO_H

#include "location.h"

#include <string>

namespace inventory {

struct CustomerInfo {
  CustomerInfo();
  CustomerInfo(const std::string&);
  bool isFrom(const Location) const;

private:
  std::string passport_id;
};

}  // namespace inventory

#endif
