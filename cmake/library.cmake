include(GenerateExportHeader)
include(CMakePackageConfigHelpers)

function(library_header_only_init LIB_NAME)
    target_include_directories(${LIB_NAME} INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>  
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
        $<INSTALL_INTERFACE:include> 
    )
endfunction()

function(library_init LIB_NAME)
    set_target_properties(${LIB_NAME} PROPERTIES
        C_VISIBILITY_PRESET hidden
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN ON
    )

    warning_as_error_enable(${LIB_NAME})

    target_include_directories(${LIB_NAME} PRIVATE
        ${CMAKE_BINARY_DIR}/include
    )

    target_include_directories(${LIB_NAME} PUBLIC
        $<INSTALL_INTERFACE:include> 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>  
    )

    target_link_directories(${LIB_NAME} PUBLIC
        $<INSTALL_INTERFACE:lib> 
    )
endfunction()




function(library_install LIB_NAME)
    install(TARGETS ${LIB_NAME} EXPORT ${LIB_NAME}-targets DESTINATION lib/niu2x)
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/niu2x DESTINATION include)
    install(EXPORT ${LIB_NAME}-targets
        FILE ${LIB_NAME}-targets.cmake
        DESTINATION lib/cmake/niu2x/
        # NAMESPACE niu2x::
    )

    configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake_install_config.in
        "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}-config.cmake"
        INSTALL_DESTINATION "lib/cmake/niu2x"
        NO_SET_AND_CHECK_MACRO
        NO_CHECK_REQUIRED_COMPONENTS_MACRO
    )

    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}-config-version.cmake"
        VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
        COMPATIBILITY AnyNewerVersion
    )

    install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}-config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}-config-version.cmake
        DESTINATION lib/cmake/niu2x
    )
endfunction()