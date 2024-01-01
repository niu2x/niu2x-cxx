include(GenerateExportHeader)

add_library(niu2x_core "")

file(GLOB cpp_source "src/*.cpp")

target_sources(niu2x_core PRIVATE
	${cpp_source}
)

library_init(niu2x_core)


# NXAPI 用于导入/导出动态库符号

# get_target_property(TARGET_TYPE niu2x_core TYPE)
# if(TARGET_TYPE STREQUAL "STATIC_LIBRARY")
#     target_compile_definitions(niu2x_core PUBLIC NXAPI_STATIC)
# endif()

# generate_export_header(niu2x_core
#     EXPORT_FILE_NAME include/niu2x/api.h
#     EXPORT_MACRO_NAME NXAPI
#     DEPRECATED_MACRO_NAME DEPRECATED_NXAPI
#     INCLUDE_GUARD_NAME NXAPI_H
#     STATIC_DEFINE NXAPI_STATIC
# )

configure_file(version.h.in include/niu2x/config.h @ONLY)

library_install(niu2x_core)
install(
    FILES 
        ${CMAKE_CURRENT_BINARY_DIR}/include/niu2x/api.h 
        ${CMAKE_CURRENT_BINARY_DIR}/include/niu2x/config.h 
	DESTINATION include/niu2x/
)
