add_library(niu2x_image "")

file(GLOB cpp_source 
    "src/*.cpp"
)

target_sources(niu2x_image PRIVATE
	${cpp_source}
)

library_init(niu2x_image)
library_install(niu2x_image)

target_link_libraries(niu2x_image PUBLIC 
    niu2x_core
)
