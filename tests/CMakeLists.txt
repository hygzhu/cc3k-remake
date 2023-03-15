cmake_minimum_required(VERSION 3.10)

project(CC3K_tests)

add_executable( tests
  Rectangle.t.cpp
)

target_link_libraries(
  tests
  geometry
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
