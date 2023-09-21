#!/bin/bash

lib_name="$1"

mkdir $lib_name
mkdir -p ${lib_name}/include/niu2x/${lib_name}
mkdir -p ${lib_name}/src

cat <<EOF > ${lib_name}/cmake_install_config.in
@PACKAGE_INIT@
include ("${CMAKE_CURRENT_LIST_DIR}/niu2x_${lib_name}-targets.cmake" )
EOF


cat <<EOF > ${lib_name}/CMakeLists.txt
add_library(niu2x_${lib_name} "")

file(GLOB cpp_source 
    "src/*.cpp"
)

target_sources(niu2x_${lib_name} PRIVATE
	\${cpp_source}
)

library_init(niu2x_${lib_name})
library_install(niu2x_${lib_name})

target_link_libraries(niu2x_${lib_name} PUBLIC 
    niu2x_core
)
EOF