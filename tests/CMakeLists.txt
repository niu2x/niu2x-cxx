add_executable(test-unused test-unused.cpp)
target_link_libraries(test-unused PRIVATE nxc)

add_executable(test-raw_memory test-raw_memory.cpp)
target_link_libraries(test-raw_memory PRIVATE nxc)

add_executable(test-raw_memory_file test-raw_memory_file.cpp)
target_link_libraries(test-raw_memory_file PRIVATE nxc)

add_executable(test-file_stream test-file_stream.cpp)
target_link_libraries(test-file_stream PRIVATE nxc)

add_executable(test-archive_zip test-archive_zip.cpp)
target_link_libraries(test-archive_zip PRIVATE nxc)

add_executable(test-buffer test-buffer.cpp)
target_link_libraries(test-buffer PRIVATE nxc)