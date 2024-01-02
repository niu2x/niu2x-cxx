cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 23)
project(NIU2X_YOU_NEVER_KNOW_WHAT_I_SAY VERSION 1.1.0 LANGUAGES CXX C)

add_executable(ynkwis_wolf "")

target_sources(ynkwis_wolf PRIVATE "wolf.cpp")

find_package(niu2x_uv REQUIRED)

target_link_libraries(ynkwis_wolf PRIVATE niu2x_uv)
