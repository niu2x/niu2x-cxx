find_package(GTest REQUIRED)

file(GLOB TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test-*.cpp")

foreach(item IN LISTS TEST_FILES)
	get_filename_component(name ${item} NAME_WE)
	add_executable(${name} ${item})
	target_link_libraries(${name} PRIVATE nxc GTest::gtest_main)
	gtest_discover_tests(${name})
endforeach()
