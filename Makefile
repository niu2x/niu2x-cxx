all: build-library build-test-app

build-library: build-debug-shared-library \
				build-debug-static-library \
				build-release-shared-library \
				build-release-static-library

build-test-app: build-test-debug-app build-test-release-app

build-debug-shared-library:
	cmake -GNinja -S. \
		-Bbuild/shared/debug \
		-DBUILD_SHARED_LIBS=ON \
		-DCMAKE_BUILD_TYPE=Debug;
	cmake --build build/shared/debug -j;
	cmake --install build/shared/debug --prefix build/shared/debug/dist;

build-debug-static-library:
	cmake -GNinja -S. \
		-Bbuild/static/debug \
		-DBUILD_SHARED_LIBS=OFF \
		-DCMAKE_BUILD_TYPE=Debug;
	cmake --build build/static/debug -j;
	cmake --install build/static/debug --prefix build/static/debug/dist/

build-release-shared-library:
	cmake -GNinja -S. \
		-Bbuild/shared/release \
		-DBUILD_SHARED_LIBS=ON \
		-DCMAKE_BUILD_TYPE=Release;
	cmake --build build/shared/release -j;
	cmake --install build/shared/release --prefix build/shared/release/dist;

build-release-static-library:
	cmake -GNinja -S. \
		-Bbuild/static/release \
		-DBUILD_SHARED_LIBS=OFF \
		-DCMAKE_BUILD_TYPE=Release;
	cmake --build build/static/release -j;
	cmake --install build/static/release --prefix build/static/release/dist/

build-test-debug-app:
	cmake -GNinja -S test-app -Bbuild/test-app-static/debug \
		-Dniu2x_filesystem_DIR=$$PWD/build/static/debug/dist/lib/cmake/niu2x \
		-Dniu2x_stream_DIR=$$PWD/build/static/debug/dist/lib/cmake/niu2x \
		-Dniu2x_crypto_DIR=$$PWD/build/static/debug/dist/lib/cmake/niu2x \
		-Dniu2x_core_DIR=$$PWD/build/static/debug/dist/lib/cmake/niu2x \
		-Dniu2x_image_DIR=$$PWD/build/static/debug/dist/lib/cmake/niu2x \
		-Dniu2x_painter_DIR=$$PWD/build/static/debug/dist/lib/cmake/niu2x \
		-Dniu2x_math_DIR=$$PWD/build/static/debug/dist/lib/cmake/niu2x \
		-DCMAKE_BUILD_TYPE=Debug;
	cmake --build build/test-app-static/debug -j


build-test-release-app:
	cmake -GNinja -S test-app -Bbuild/test-app-static/release \
		-Dniu2x_filesystem_DIR=$$PWD/build/static/release/dist/lib/cmake/niu2x \
		-Dniu2x_stream_DIR=$$PWD/build/static/release/dist/lib/cmake/niu2x \
		-Dniu2x_crypto_DIR=$$PWD/build/static/release/dist/lib/cmake/niu2x \
		-Dniu2x_image_DIR=$$PWD/build/static/release/dist/lib/cmake/niu2x \
		-Dniu2x_core_DIR=$$PWD/build/static/release/dist/lib/cmake/niu2x \
		-Dniu2x_math_DIR=$$PWD/build/static/release/dist/lib/cmake/niu2x \
		-Dniu2x_painter_DIR=$$PWD/build/static/release/dist/lib/cmake/niu2x \
		-DCMAKE_BUILD_TYPE=Release;
	cmake --build build/test-app-static/release -j


build-nxlua:
	cmake -GNinja -S app/nxlua -Bbuild/nxlua/release \
		-Dniu2x_filesystem_DIR=$$PWD/build/static/release/dist/lib/cmake/niu2x \
		-Dniu2x_stream_DIR=$$PWD/build/static/release/dist/lib/cmake/niu2x \
		-Dniu2x_crypto_DIR=$$PWD/build/static/release/dist/lib/cmake/niu2x \
		-Dniu2x_image_DIR=$$PWD/build/static/release/dist/lib/cmake/niu2x \
		-Dniu2x_core_DIR=$$PWD/build/static/release/dist/lib/cmake/niu2x \
		-Dniu2x_math_DIR=$$PWD/build/static/release/dist/lib/cmake/niu2x \
		-Dniu2x_lua_DIR=$$PWD/build/static/release/dist/lib/cmake/niu2x \
		-Dniu2x_painter_DIR=$$PWD/build/static/release/dist/lib/cmake/niu2x \
		-DCMAKE_BUILD_TYPE=Release;
	cmake --build build/nxlua/release -j


.PHONY: 
