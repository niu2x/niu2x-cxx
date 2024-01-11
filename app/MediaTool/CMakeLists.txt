cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 23)
project(NIU2X_MediaTool VERSION 1.1.0 LANGUAGES CXX C)

add_executable(MediaTool "")

target_sources(MediaTool PRIVATE "main.cpp")

find_package(niu2x_filesystem REQUIRED)
find_package(niu2x_math REQUIRED)
find_package(niu2x_bite REQUIRED)
find_package(niu2x_media REQUIRED)

target_link_libraries(MediaTool PRIVATE 
	niu2x_filesystem 
	niu2x_math
	niu2x_bite
	niu2x_media
)

install(TARGETS MediaTool DESTINATION bin)