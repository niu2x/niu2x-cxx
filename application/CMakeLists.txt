add_library(niu2x_application "")

file(GLOB cpp_source 
    "src/*.cpp"
)

target_sources(niu2x_application PRIVATE
	${cpp_source}
)

library_init(niu2x_application)
library_install(niu2x_application)

target_link_libraries(niu2x_application PUBLIC 
    niu2x_core
)
