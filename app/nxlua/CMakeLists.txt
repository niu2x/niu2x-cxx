cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 23)
project(NIU2X_LUA VERSION 1.1.0 LANGUAGES CXX C)

add_executable(nxlua "")

target_sources(nxlua PRIVATE "main.cpp")

find_package(niu2x_lua REQUIRED)

target_link_libraries(nxlua PRIVATE niu2x_lua)
