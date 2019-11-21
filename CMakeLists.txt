cmake_minimum_required(VERSION 3.2)

project(Inventory-MinCost)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Werror)

set (INCLUDE_LIST "include")
include_directories(${INCLUDE_LIST})

set(SRC_LIST
  "source/cost_calculator.cc"
  "source/customer_info.cc"
  "source/item_type.cc"
  "source/location.cc"
  "source/order.cc"
  "source/order_service.cc"
  "source/order_service_adapter.cc"
  "source/order_status.cc"
  "source/repository_service.cc")

#add_executable(${PROJECT_NAME} "main.cpp")

set(TEST_TARGET "${PROJECT_NAME}-Test")

include_directories(${INCLUDE_LIST} "usr/include/gtest")

add_executable(${TEST_TARGET} ${SRC_LIST} "test/inventory_test.cc")

target_link_libraries(${TEST_TARGET} gtest gtest_main pthread)
