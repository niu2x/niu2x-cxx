cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)
project(NIU2X_TEST_APP)

find_package(niu2x_core REQUIRED)
find_package(niu2x_filesystem REQUIRED)

add_executable(touch "touch.cpp")
target_link_libraries(touch PRIVATE niu2x_filesystem)