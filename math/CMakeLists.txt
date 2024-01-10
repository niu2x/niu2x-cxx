add_library(niu2x_math "")

file(GLOB cpp_source 
    "src/*.cpp"
)

target_sources(niu2x_math PRIVATE
	${cpp_source}
)

library_init(niu2x_math)
library_install(niu2x_math)

target_link_libraries(niu2x_math PUBLIC 
    niu2x_core
    fftw3
)
