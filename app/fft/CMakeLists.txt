cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 23)
project(NIU2X_fft VERSION 1.1.0 LANGUAGES CXX C)

add_executable(fft "")

target_sources(fft PRIVATE "main.cpp")

find_package(niu2x_filesystem REQUIRED)
find_package(niu2x_image REQUIRED)
find_package(niu2x_math REQUIRED)
find_package(niu2x_bite REQUIRED)

target_link_libraries(fft PRIVATE 
	niu2x_filesystem 
	niu2x_image
	niu2x_math
	niu2x_bite
)

install(TARGETS fft DESTINATION bin)