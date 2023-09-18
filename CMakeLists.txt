cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)
project(NIU2X_NXC VERSION 0.1.2 LANGUAGES CXX C)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
# include(external_deps)
include(warning_as_error)
include(library)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(NIU2X_USE_POSIX 1)    
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(NIU2X_USE_WINAPI 1)    
endif()

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(core)
