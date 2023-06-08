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



	if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
		file(COPY "${PROJECT_BINARY_DIR}/external_deps/bin/gtest_main.dll" DESTINATION Debug)
		file(COPY "${PROJECT_BINARY_DIR}/external_deps/bin/gtest.dll" DESTINATION Debug)

		file(COPY "${PROJECT_BINARY_DIR}/external_deps/bin/gtest_main.dll" DESTINATION Release)
		file(COPY "${PROJECT_BINARY_DIR}/external_deps/bin/gtest.dll" DESTINATION Release)
	endif()
endif()



if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	add_executable(lisp "")

	find_package(FLEX 2.6 REQUIRED)
	find_package(BISON 2 REQUIRED)

	flex_target(LEXER "lisp.l" "${CMAKE_CURRENT_BINARY_DIR}/lisp-lexer.c" 
		DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/lisp-lexer.h"
		COMPILE_FLAGS "--prefix=lisp"
	)

	bison_target(PARSER "lisp.y" "${CMAKE_CURRENT_BINARY_DIR}/lisp-parser.c" 
		DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/lisp-parser.h"
		COMPILE_FLAGS "--name-prefix=lisp"
	)

	add_flex_bison_dependency(LEXER PARSER)

	target_sources(lisp PRIVATE 
		lisp_main.cpp
		lisp.cpp
		${CMAKE_CURRENT_BINARY_DIR}/lisp-lexer.c
		${CMAKE_CURRENT_BINARY_DIR}/lisp-parser.c
	)


	target_include_directories(lisp PRIVATE 
		${CMAKE_CURRENT_BINARY_DIR} 
		${CMAKE_CURRENT_SOURCE_DIR}
	)
	target_link_libraries(lisp PRIVATE nxc )
endif()