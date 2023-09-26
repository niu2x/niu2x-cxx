cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)
project(NIU2X_CPP_LIBRARY VERSION 1.1.0 LANGUAGES CXX C)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
# include(external_deps)
include(warning_as_error)
include(library)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(NIU2X_USE_POSIX ON)    
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(NIU2X_USE_WINAPI ON)    
endif()

set(CMAKE_CXX_STANDARD 23)

configure_file(build_config.h.in include/build_time/build_config.h)

add_subdirectory(core)
add_subdirectory(filesystem)
add_subdirectory(crypto)
add_subdirectory(stream)
add_subdirectory(math)
add_subdirectory(image)
add_subdirectory(painter)
add_subdirectory(lua)

include(CPack)
