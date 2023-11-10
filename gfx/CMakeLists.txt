add_library(niu2x_gfx "")

file(GLOB cpp_source 
    "src/*.cpp"
    "src/gui/*.cpp"
)

target_sources(niu2x_gfx PRIVATE
	${cpp_source}
    src/glad/src/glad.c
)

library_init(niu2x_gfx)
library_install(niu2x_gfx)

target_link_libraries(niu2x_gfx PUBLIC 
    niu2x_math
    niu2x_stream
    niu2x_image
    niu2x_lua
)


target_include_directories(niu2x_gfx PRIVATE src/glad/include)

find_package(glfw3 REQUIRED)
find_package(Freetype REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(yoga REQUIRED)
find_package(pugixml REQUIRED)

target_link_libraries(niu2x_gfx PUBLIC
    glfw
    dl
    Freetype::Freetype
    yaml-cpp::yaml-cpp
    yoga::yogacore
    pugixml
)

