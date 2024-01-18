cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 23)
project(NIU2X_YOU_NEVER_KNOW_WHAT_I_SAY VERSION 1.1.0 LANGUAGES CXX C)

add_library(niupy SHARED "")

target_sources(niupy PRIVATE "main.cpp")

find_package(niu2x_media REQUIRED)
find_package(niu2x_stream REQUIRED)


target_link_libraries(niupy PRIVATE 
	niu2x_media
	niu2x_stream
)


execute_process(COMMAND python -m pybind11 --includes
	OUTPUT_VARIABLE PYBIND11_INCLUDES
	OUTPUT_STRIP_TRAILING_WHITESPACE
)

string(REGEX REPLACE "^\\-I" "" PYBIND11_INCLUDES ${PYBIND11_INCLUDES})
string(REPLACE " -I" ";" PYBIND11_INCLUDES ${PYBIND11_INCLUDES})

target_include_directories(niupy PRIVATE ${PYBIND11_INCLUDES})

 


execute_process(COMMAND python3-config --extension-suffix
	OUTPUT_VARIABLE SO_SUFFIX
	OUTPUT_STRIP_TRAILING_WHITESPACE
)

set_target_properties(niupy PROPERTIES SUFFIX ${SO_SUFFIX})
