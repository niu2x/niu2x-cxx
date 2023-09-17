set(LIB_NAME noncopyable)
add_library(${LIB_NAME} INTERFACE "")
library_header_only_init(${LIB_NAME})

library_install(${LIB_NAME})
