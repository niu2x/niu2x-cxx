cmake_minimum_required(VERSION 3.17.0 FATAL_ERROR)
project(ModelViewer VERSION 0.1.0 LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 20)

find_package(OGRE REQUIRED)
find_package(niu2x_application REQUIRED)
find_package(niu2x_filesystem REQUIRED)

add_executable(ModelViewer src/main.cpp)
target_link_libraries(ModelViewer PUBLIC 
	OgreMain 
	OgreBites 
	OgreOverlay 
	niu2x_application 
	niu2x_filesystem)

function(copy_file path)
	add_custom_command(TARGET ModelViewer 
		POST_BUILD
		COMMAND 
		${CMAKE_COMMAND} -E copy_if_different ${path} $<TARGET_FILE_DIR:ModelViewer>)
endfunction()

copy_file("${CMAKE_CURRENT_SOURCE_DIR}/cfg/resources.cfg")
copy_file("${CMAKE_CURRENT_SOURCE_DIR}/cfg/plugins.cfg")

