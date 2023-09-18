add_library(niu2x_core "")
target_sources(niu2x_core PRIVATE
	src/core.cpp
)

library_init(niu2x_core)
library_install(niu2x_core)