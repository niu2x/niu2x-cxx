add_library(niu2x_formatter "")

file(GLOB cpp_source 
    "src/*.cpp"
)

target_sources(niu2x_formatter PRIVATE
	${cpp_source}
)

library_init(niu2x_formatter)
library_install(niu2x_formatter)

target_link_libraries(niu2x_formatter PUBLIC 
    niu2x_core
)
