add_library(niu2x_media "")

file(GLOB cpp_source 
    "src/*.cpp"
)

target_sources(niu2x_media PRIVATE
	${cpp_source}
)

library_init(niu2x_media)
library_install(niu2x_media)

target_link_libraries(niu2x_media PUBLIC 
    niu2x_core
    niu2x_resource
)
