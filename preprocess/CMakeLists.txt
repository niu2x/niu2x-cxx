set(LIB_NAME preprocess)
add_library(${LIB_NAME} INTERFACE "")
library_header_only_init(${LIB_NAME})

# configure_file(config.h.in include/nxc/config.h @ONLY)
library_install(${LIB_NAME})