cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 23)
project(NIU2X_LUA VERSION 1.1.0 LANGUAGES CXX C)

add_executable(watchdog "")

target_sources(watchdog PRIVATE "main.cpp")

find_package(niu2x_lua REQUIRED)
find_package(niu2x_application REQUIRED)
find_package(niu2x_filesystem REQUIRED)
find_package(niu2x_uv REQUIRED)
find_package(niu2x_stream REQUIRED)

target_link_libraries(watchdog PRIVATE 
	niu2x_lua 
	niu2x_application
	niu2x_filesystem
	niu2x_uv
	niu2x_stream
)
