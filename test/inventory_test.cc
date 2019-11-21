#include <gtest/gtest.h>

#include "order_service_adapter.h"

using namespace inventory;

namespace {

static void assertFillOrder(const std::string& exptected, const std::string& order) {
  ASSERT_EQ(exptected, Store().fulfill(order));
}

}  // namespace

// BRAZIL:B123AB1234567:IPHONE:20:IPOD:10
TEST(InventoryTest, order1) {
  assertFillOrder("2650:90:100:80:50", "BRAZIL:B123AB1234567:IPHONE:20:IPOD:10");
}

// ARGENTINA:B123AB1234567:IPHONE:22:IPOD:10
TEST(InventoryTest, order2) {
  assertFillOrder("3910:90:100:80:48", "ARGENTINA:B123AB1234567:IPHONE:22:IPOD:10");
}

// BRAZIL:AAB123456789:IPHONE:125:IPOD:70
TEST(InventoryTest, order3) {
  assertFillOrder("19260:30:100:0:25", "BRAZIL:AAB123456789:IPHONE:125:IPOD:70");
}

// ARGENTINA:AAB123456789:IPOD:50:IPHONE:25
TEST(InventoryTest, order4) {
  assertFillOrder("8550:100:50:80:45", "ARGENTINA:AAB123456789:IPOD:50:IPHONE:25");
}

// BRAZIL:IPHONE:50:IPOD:150
TEST(InventoryTest, order5) {
  assertFillOrder("18500:0:50:50:50", "BRAZIL:IPHONE:50:IPOD:150");
}

// BRAZIL:IPHONE:250:IPOD:150
TEST(InventoryTest, order6) {
  assertFillOrder("OUT_OF_STOCK:100:100:100:50", "BRAZIL:IPHONE:250:IPOD:150");
}
