add_library(niu2x_bite "")

file(GLOB cpp_source 
    "src/*.cpp"
)

target_sources(niu2x_bite PRIVATE
	${cpp_source}
)

library_init(niu2x_bite)
library_install(niu2x_bite)

target_link_libraries(niu2x_bite PUBLIC 
    niu2x_core
)
