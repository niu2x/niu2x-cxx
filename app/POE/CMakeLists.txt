cmake_minimum_required(VERSION 3.17.0 FATAL_ERROR)
project(POE VERSION 0.1.0 LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 20)

find_package(OGRE REQUIRED)
find_package(niu2x_application REQUIRED)
find_package(niu2x_filesystem REQUIRED)

file(GLOB cpp_source 
    "src/*.cpp"
)

add_executable(POE ${cpp_source})
target_link_libraries(POE PUBLIC 
	OgreMain 
	OgreBites 
	OgreOverlay 
	niu2x_application 
	niu2x_filesystem)

function(copy_file path)
	add_custom_command(TARGET POE 
		POST_BUILD
		COMMAND 
		${CMAKE_COMMAND} -E copy_if_different ${path} $<TARGET_FILE_DIR:POE>)
endfunction()

copy_file("${CMAKE_CURRENT_SOURCE_DIR}/cfg/resources.cfg")
copy_file("${CMAKE_CURRENT_SOURCE_DIR}/cfg/plugins.cfg")

