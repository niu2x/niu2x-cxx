add_library(niu2x_stream "")

file(GLOB cpp_source 
    "src/*.cpp"
    "src/filter_alg/*.cpp"
)

target_sources(niu2x_stream PRIVATE
	${cpp_source}
)

library_init(niu2x_stream)
library_install(niu2x_stream)

target_link_libraries(niu2x_stream PUBLIC 
    niu2x_filesystem
    niu2x_crypto
)