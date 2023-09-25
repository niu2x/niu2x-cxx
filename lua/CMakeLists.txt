add_library(niu2x_lua "")

file(GLOB cpp_source 
    "src/*.cpp"
)

target_sources(niu2x_lua PRIVATE
	${cpp_source}
)

library_init(niu2x_lua)
library_install(niu2x_lua)

target_link_libraries(niu2x_lua PUBLIC 
    niu2x_core
)


