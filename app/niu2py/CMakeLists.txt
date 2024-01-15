cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 23)
project(NIU2X_YOU_NEVER_KNOW_WHAT_I_SAY VERSION 1.1.0 LANGUAGES CXX C)

add_library(niu2py SHARED "")

target_sources(niu2py PRIVATE "main.cpp")

find_package(niu2x_media REQUIRED)

target_link_libraries(niu2py PRIVATE niu2x_media)

target_include_directories(niu2py PRIVATE 
	/home/niu2x/bin/miniconda3/include/python3.10
	/home/niu2x/bin/miniconda3/lib/python3.10/site-packages/pybind11/include
)

 
