cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 23)
project(NIU2X_imgcvt VERSION 1.1.0 LANGUAGES CXX C)

add_executable(imgcvt "")

target_sources(imgcvt PRIVATE "main.cpp")

find_package(niu2x_filesystem REQUIRED)
find_package(niu2x_image REQUIRED)

target_link_libraries(imgcvt PRIVATE niu2x_filesystem niu2x_image)
