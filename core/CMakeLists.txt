add_library(niu2x_core "")

file(GLOB cpp_source "src/*.cpp")

target_sources(niu2x_core PRIVATE
	${cpp_source}
)

library_init(niu2x_core)
library_install(niu2x_core)


generate_export_header(niu2x_core
    EXPORT_FILE_NAME include/niu2x/api.h
    EXPORT_MACRO_NAME NXAPI
    DEPRECATED_MACRO_NAME DEPRECATED_NXAPI
    INCLUDE_GUARD_NAME NXAPI_H
)

configure_file(version.h.in include/niu2x/config.h @ONLY)

install(
    FILES 
        ${CMAKE_CURRENT_BINARY_DIR}/include/niu2x/api.h 
        ${CMAKE_CURRENT_BINARY_DIR}/include/niu2x/config.h 
	DESTINATION include/niu2x/
)
