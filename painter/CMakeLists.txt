add_library(niu2x_painter "")

file(GLOB cpp_source 
    "src/*.cpp"
)

target_sources(niu2x_painter PRIVATE
	${cpp_source}
)

library_init(niu2x_painter)
library_install(niu2x_painter)

target_link_libraries(niu2x_painter PUBLIC 
    niu2x_image
)
