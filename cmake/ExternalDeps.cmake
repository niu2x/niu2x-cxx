include(ExternalProject)

# boost
# set(TMP_CMAKE_ARGS "")
# list(APPEND TMP_CMAKE_ARGS "-DCMAKE_BUILD_TYPE=Release")
# list(APPEND TMP_CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${PROJECT_BINARY_DIR}/external_deps")
# list(APPEND TMP_CMAKE_ARGS "-DBUILD_SHARED_LIBS=OFF")

# ExternalProject_Add(external_boost
#     GIT_REPOSITORY  https://gitee.com/add358/boost
#     GIT_TAG         1.71.0
#     CMAKE_ARGS      ${TMP_CMAKE_ARGS}
#     CONFIGURE_COMMAND ""
#     # BUILD_COMMAND  ""
#     BUILD_COMMAND   "${PROJECT_SOURCE_DIR}/tools/build_boost.sh"
#     INSTALL_COMMAND ""
# )

# zlib
set(TMP_CMAKE_ARGS "")
list(APPEND TMP_CMAKE_ARGS "-DCMAKE_BUILD_TYPE=Release")
list(APPEND TMP_CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${PROJECT_BINARY_DIR}/external_deps")
list(APPEND TMP_CMAKE_ARGS "-DBUILD_SHARED_LIBS=OFF")
list(APPEND TMP_CMAKE_ARGS "-DCMAKE_POSITION_INDEPENDENT_CODE=ON")
list(APPEND TMP_CMAKE_ARGS "-DONLY_INSTALL_STATIC_LIBRARY=ON")

ExternalProject_Add(external_zlib
    GIT_REPOSITORY  https://gitee.com/niu2x/zlib.git
    GIT_TAG         v1.2.13.1
    CMAKE_ARGS      ${TMP_CMAKE_ARGS}
)
set(ZLIB_ROOT "${PROJECT_BINARY_DIR}/external_deps")

# libzip
set(TMP_CMAKE_ARGS "")
list(APPEND TMP_CMAKE_ARGS "-DCMAKE_BUILD_TYPE=Release")
list(APPEND TMP_CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${PROJECT_BINARY_DIR}/external_deps")
list(APPEND TMP_CMAKE_ARGS "-DBUILD_SHARED_LIBS=OFF")
list(APPEND TMP_CMAKE_ARGS "-DCMAKE_POSITION_INDEPENDENT_CODE=ON")
list(APPEND TMP_CMAKE_ARGS "-DENABLE_COMMONCRYPTO=OFF")
list(APPEND TMP_CMAKE_ARGS "-DENABLE_GNUTLS=OFF")
list(APPEND TMP_CMAKE_ARGS "-DENABLE_MBEDTLS=OFF")
list(APPEND TMP_CMAKE_ARGS "-DENABLE_OPENSSL=OFF")
list(APPEND TMP_CMAKE_ARGS "-DENABLE_WINDOWS_CRYPTO=OFF")
list(APPEND TMP_CMAKE_ARGS "-DENABLE_BZIP2=OFF")
list(APPEND TMP_CMAKE_ARGS "-DENABLE_LZMA=OFF")
list(APPEND TMP_CMAKE_ARGS "-DENABLE_ZSTD=OFF")
list(APPEND TMP_CMAKE_ARGS "-DZLIB_ROOT=${ZLIB_ROOT}")

ExternalProject_Add(external_libzip
    GIT_REPOSITORY  https://gitee.com/kaikong/libzip.git
    GIT_TAG         v1.9.2   
    CMAKE_ARGS      ${TMP_CMAKE_ARGS}
)
set(libzip_DIR "${PROJECT_BINARY_DIR}/external_deps/lib/cmake/libzip")

add_dependencies(external_libzip external_zlib)

# googletest
set(TMP_CMAKE_ARGS "")
list(APPEND TMP_CMAKE_ARGS "-DCMAKE_BUILD_TYPE=Release")
list(APPEND TMP_CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${PROJECT_BINARY_DIR}/external_deps")
list(APPEND TMP_CMAKE_ARGS "-DBUILD_SHARED_LIBS=ON")
ExternalProject_Add(external_googletest
    GIT_REPOSITORY  https://gitee.com/zqx5449/googletest
    GIT_TAG         v1.13.0   
    CMAKE_ARGS      ${TMP_CMAKE_ARGS}
)
set(GTest_DIR "${PROJECT_BINARY_DIR}/external_deps/lib/cmake/GTest")

# curl
set(TMP_CMAKE_ARGS "")
list(APPEND TMP_CMAKE_ARGS "-DCMAKE_BUILD_TYPE=Release")
list(APPEND TMP_CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${PROJECT_BINARY_DIR}/external_deps")
list(APPEND TMP_CMAKE_ARGS "-DBUILD_SHARED_LIBS=OFF")
list(APPEND TMP_CMAKE_ARGS "-DCMAKE_POSITION_INDEPENDENT_CODE=ON")
list(APPEND TMP_CMAKE_ARGS "-DHTTP_ONLY=ON")
list(APPEND TMP_CMAKE_ARGS "-DZLIB_ROOT=${ZLIB_ROOT}")


ExternalProject_Add(external_curl
    GIT_REPOSITORY  https://github.com/curl/curl
    GIT_TAG         curl-8_1_1
    CMAKE_ARGS      ${TMP_CMAKE_ARGS}
)
set(CURL_ROOT "${PROJECT_BINARY_DIR}/external_deps")
add_dependencies(external_curl external_zlib)
