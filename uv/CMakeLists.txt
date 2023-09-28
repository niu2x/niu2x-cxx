add_subdirectory(src/uv-1.46.0)

add_library(niu2x_uv $<TARGET_OBJECTS:uv>)

file(GLOB cpp_source 
    "src/*.cpp"
)

target_sources(niu2x_uv PRIVATE
	${cpp_source}
)

library_init(niu2x_uv)
library_install(niu2x_uv)

target_link_libraries(niu2x_uv PUBLIC 
    niu2x_core
)

target_include_directories(niu2x_uv PRIVATE src/uv-1.46.0/include)

get_target_property(uv_sys_libraries uv INTERFACE_LINK_LIBRARIES)
target_link_libraries(niu2x_uv PUBLIC ${uv_sys_libraries})
