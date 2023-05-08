if(GTest_DIR) 
	find_package(GTest REQUIRED)
	file(GLOB TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test-*.cpp")

	foreach(item IN LISTS TEST_FILES)
		get_filename_component(name ${item} NAME_WE)
		add_executable(${name} ${item})
		target_link_libraries(${name} PRIVATE nxc GTest::gtest_main)
		gtest_discover_tests(${name})

	endforeach()


	file(GLOB TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/testx-*.cpp")
	foreach(item IN LISTS TEST_FILES)
		get_filename_component(name ${item} NAME_WE)
		add_executable(${name} ${item})
		target_link_libraries(${name} PRIVATE nxc )
	endforeach()



	if(WIN32) 
		file(COPY "${PROJECT_BINARY_DIR}/external_deps/bin/gtest_main.dll" DESTINATION Debug)
		file(COPY "${PROJECT_BINARY_DIR}/external_deps/bin/gtest.dll" DESTINATION Debug)

		file(COPY "${PROJECT_BINARY_DIR}/external_deps/bin/gtest_main.dll" DESTINATION Release)
		file(COPY "${PROJECT_BINARY_DIR}/external_deps/bin/gtest.dll" DESTINATION Release)
	endif()
endif()






add_executable(t-lexer "")

find_package(FLEX 2.6 REQUIRED)
find_package(BISON 2 REQUIRED)

flex_target(LEXER "jp.l" "${CMAKE_CURRENT_BINARY_DIR}/jp-lexer.c" 
	DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/jp-lexer.h"
	COMPILE_FLAGS "--prefix=jp"
)

target_sources(t-lexer PRIVATE 
	t-lexer.cpp
	${CMAKE_CURRENT_BINARY_DIR}/jp-lexer.c
)


target_include_directories(t-lexer PRIVATE 
	${CMAKE_CURRENT_BINARY_DIR} 
	${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(t-lexer PRIVATE nxc )
