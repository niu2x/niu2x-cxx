add_library(niu2x_resource "")

file(GLOB cpp_source 
    "src/*.cpp"
)

target_sources(niu2x_resource PRIVATE
	${cpp_source}
)

library_init(niu2x_resource)
library_install(niu2x_resource)

target_link_libraries(niu2x_resource PUBLIC 
    niu2x_filesystem
    niu2x_stream
)
