cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 23)
project(NIU2X_POE VERSION 1.1.0 LANGUAGES CXX C)

add_executable(poe "")

target_sources(poe PRIVATE "main.cpp")

find_package(niu2x_lua REQUIRED)
find_package(niu2x_application REQUIRED)
find_package(niu2x_filesystem REQUIRED)
find_package(niu2x_uv REQUIRED)
find_package(niu2x_stream REQUIRED)
find_package(niu2x_gfx REQUIRED)

target_link_libraries(poe PRIVATE 
	niu2x_gfx
	niu2x_application
)
