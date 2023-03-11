cmake_minimum_required(VERSION 3.10)

project(CC3K_tests)

add_executable( tests
  boundingrectangle.t.cpp
)

target_link_libraries(
  tests
  CC3K_lib
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
