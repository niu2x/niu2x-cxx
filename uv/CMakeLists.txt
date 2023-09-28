add_library(niu2x_uv "")

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

add_subdirectory(src/uv-1.46.0)