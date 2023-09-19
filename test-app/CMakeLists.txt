cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)
project(NIU2X_TEST_APP)
set(CMAKE_CXX_STANDARD 17)

find_package(niu2x_core REQUIRED)
find_package(niu2x_filesystem REQUIRED)
find_package(niu2x_stream REQUIRED)

add_executable(touch "touch.cpp")
target_link_libraries(touch PRIVATE niu2x_filesystem)

add_executable(make_dir "make_dir.cpp")
target_link_libraries(make_dir PRIVATE niu2x_filesystem)

add_executable(make_dirs "make_dirs.cpp")
target_link_libraries(make_dirs PRIVATE niu2x_filesystem)

add_executable(remove "remove.cpp")
target_link_libraries(remove PRIVATE niu2x_filesystem)

add_executable(file "file.cpp")
target_link_libraries(file PRIVATE niu2x_stream)
