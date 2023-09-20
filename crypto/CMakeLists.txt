add_library(niu2x_crypto "")

file(GLOB cpp_source 
    "src/*.cpp"
)

target_sources(niu2x_crypto PRIVATE
	${cpp_source}
)

library_init(niu2x_crypto)
library_install(niu2x_crypto)

target_link_libraries(niu2x_crypto PUBLIC 
    niu2x_core
)