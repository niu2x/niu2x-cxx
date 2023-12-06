LIB_DEBUG_BUILD := build/debug
LIB_RELEASE_BUILD := build/release

LIB_DEBUG_DIST := dist/debug
LIB_RELEASE_DIST := dist/release

LIB_DIR := $(PWD)/$(LIB_RELEASE_DIST)/lib/cmake/niu2x

all: release-library all-app

# build niu2x library
library: debug-library \
				release-library

debug-library:
	cmake -GNinja -S. \
		-B $(LIB_DEBUG_BUILD) \
		-DBUILD_SHARED_LIBS=OFF \
		-DCMAKE_BUILD_TYPE=Debug;
	cmake --build $(LIB_DEBUG_BUILD) -j;
	cmake --install $(LIB_DEBUG_BUILD) --prefix $(LIB_DEBUG_DIST)

release-library:
	cmake -GNinja -S. \
		-B $(LIB_RELEASE_BUILD) \
		-DBUILD_SHARED_LIBS=OFF \
		-DCMAKE_BUILD_TYPE=Release;
	cmake --build $(LIB_RELEASE_BUILD) -j;
	cmake --install $(LIB_RELEASE_BUILD) --prefix $(LIB_RELEASE_DIST)


# build test app
test-app: release-library
	cmake -GNinja -S test-app -Bbuild/test-app-static/release \
		-Dniu2x_filesystem_DIR=$(LIB_DIR) \
		-Dniu2x_stream_DIR=$(LIB_DIR) \
		-Dniu2x_crypto_DIR=$(LIB_DIR) \
		-Dniu2x_core_DIR=$(LIB_DIR) \
		-Dniu2x_image_DIR=$(LIB_DIR) \
		-Dniu2x_painter_DIR=$(LIB_DIR) \
		-Dniu2x_math_DIR=$(LIB_DIR) \
		-Dniu2x_uv_DIR=$(LIB_DIR) \
		-Dniu2x_application_DIR=$(LIB_DIR) \
		-DCMAKE_BUILD_TYPE=Release;
	cmake --build build/test-app-static -j

# build app
all-app: nxlua watchdog ModelViewer

nxlua: release-library
	cmake -GNinja -S app/nxlua -Bbuild/nxlua \
		-Dniu2x_lua_DIR=$(LIB_DIR) \
		-DCMAKE_BUILD_TYPE=Release;
	cmake --build build/nxlua -j

watchdog: release-library
	cmake -GNinja -S app/watchdog -Bbuild/watchdog \
		-Dniu2x_filesystem_DIR=$(LIB_DIR) \
		-Dniu2x_lua_DIR=$(LIB_DIR) \
		-Dniu2x_uv_DIR=$(LIB_DIR) \
		-Dniu2x_stream_DIR=$(LIB_DIR) \
		-Dniu2x_application_DIR=$(LIB_DIR) \
		-DCMAKE_BUILD_TYPE=Release;
	cmake --build build/watchdog -j


ModelViewer: release-library
	cmake -S app/ModelViewer -Bbuild/ModelViewer -DCMAKE_BUILD_TYPE=Release \
		-D niu2x_application_DIR=$(LIB_DIR) \
		-D niu2x_filesystem_DIR=$(LIB_DIR)
	cmake --build build/ModelViewer

.PHONY: library \
		debug-library \
		release-library \
		test-app \
		nxlua \
		watchdog \
		all-app \
		all \
		ModelViewer
