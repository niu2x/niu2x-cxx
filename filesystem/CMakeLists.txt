add_library(niu2x_filesystem "")

file(GLOB cpp_source 
    "src/*.cpp"
)

target_sources(niu2x_filesystem PRIVATE
	${cpp_source}
)

library_init(niu2x_filesystem)
library_install(niu2x_filesystem)

target_link_libraries(niu2x_filesystem PUBLIC 
    niu2x_core
)