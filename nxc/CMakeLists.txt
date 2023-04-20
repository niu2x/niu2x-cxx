set(LIB_NAME nxc)
set(EXPORT_LIB_NAME niu2x::nxc)

add_library(${LIB_NAME} "")

include(GenerateExportHeader)
generate_export_header(${LIB_NAME}
    EXPORT_FILE_NAME include/${LIB_NAME}/api.h
    EXPORT_MACRO_NAME NXC_API
    DEPRECATED_MACRO_NAME NXC_DEPRECATED_API
    INCLUDE_GUARD_NAME NXC_API_H
)


warning_as_error_enable(${LIB_NAME})
set_target_properties(${LIB_NAME} PROPERTIES
    C_VISIBILITY_PRESET hidden
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
)

list(APPEND SOURCE_DIRECTORIES "src/*.cpp")

set(PRIVATE_LIBS "")
set(PUBLIC_LIBS "")
set(THIRD_PARTY_LIBS "")

file(GLOB source 
    ${SOURCE_DIRECTORIES}
)

target_sources(${LIB_NAME} PRIVATE
    ${source}
)

target_include_directories(${LIB_NAME} PRIVATE
    src/
)

target_include_directories(${LIB_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>  
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/external_boost-prefix/src/external_boost>  
    $<INSTALL_INTERFACE:include> 
)

target_link_directories(${LIB_NAME} PUBLIC
    $<INSTALL_INTERFACE:lib> 
)

list(APPEND THIRD_PARTY_LIBS zip z)

if(${BUILD_SHARED_LIBS})
    list(APPEND PRIVATE_LIBS ${THIRD_PARTY_LIBS})
else()
    list(APPEND PUBLIC_LIBS ${THIRD_PARTY_LIBS})
endif()

target_link_libraries(${LIB_NAME} PRIVATE
    ${PRIVATE_LIBS}
)

target_link_libraries(${LIB_NAME} PUBLIC
    ${PUBLIC_LIBS}
)

if(${BUILD_SHARED_LIBS})
    target_link_directories(${LIB_NAME} PRIVATE
        "${PROJECT_BINARY_DIR}/external_deps/lib"
    )
else()
    target_link_directories(${LIB_NAME} PUBLIC
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/external_deps/lib>  
    )
endif()

target_include_directories(${LIB_NAME} PRIVATE
    "${PROJECT_BINARY_DIR}/external_deps/include"
)

configure_file(config.h.in include/nxc/config.h @ONLY)

install(TARGETS ${LIB_NAME}
    EXPORT nxc-targets
    DESTINATION lib)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/nxc DESTINATION include)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/nxc DESTINATION include)
install(DIRECTORY ${PROJECT_BINARY_DIR}/external_boost-prefix/src/external_boost/boost DESTINATION include)


if(${BUILD_SHARED_LIBS})
else()
    file(GLOB LIB_FILES "${PROJECT_BINARY_DIR}/external_deps/lib/*.a")
    install(FILES ${LIB_FILES} DESTINATION lib)
endif()


install(EXPORT nxc-targets
    FILE nxc-targets.cmake
    DESTINATION lib/cmake/niu2x/
    NAMESPACE niu2x::
)

include(CMakePackageConfigHelpers)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake_install_config.in
    "${CMAKE_CURRENT_BINARY_DIR}/nxc-config.cmake"
    INSTALL_DESTINATION "lib/cmake/niu2x"
    NO_SET_AND_CHECK_MACRO
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/nxc-config-version.cmake"
    VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
    COMPATIBILITY AnyNewerVersion
)


install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/nxc-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/nxc-config-version.cmake
    DESTINATION lib/cmake/niu2x
)

