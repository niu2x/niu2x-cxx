build-library: build-debug-library \
				build-release-library

build-debug-library:
	cmake -GNinja -S. \
		-Bbuild/debug \
		-DBUILD_SHARED_LIBS=OFF \
		-DCMAKE_BUILD_TYPE=Debug;
	cmake --build build/debug -j;
	cmake --install build/debug --prefix build/debug/dist/


build-release-library:
	cmake -GNinja -S. \
		-Bbuild/release \
		-DBUILD_SHARED_LIBS=OFF \
		-DCMAKE_BUILD_TYPE=Release;
	cmake --build build/release -j;
	cmake --install build/release --prefix build/release/dist/

build-nxlua: build-release-library
	cmake -GNinja -S app/nxlua -Bbuild/nxlua/release \
		-Dniu2x_lua_DIR=$$PWD/build/release/dist/lib/cmake/niu2x \
		-DCMAKE_BUILD_TYPE=Release;
	cmake --build build/nxlua/release -j


build-test-app: build-debug-library
	cmake -GNinja -S test-app -Bbuild/test-app-static/debug \
		-Dniu2x_filesystem_DIR=$$PWD/build/debug/dist/lib/cmake/niu2x \
		-Dniu2x_stream_DIR=$$PWD/build/debug/dist/lib/cmake/niu2x \
		-Dniu2x_crypto_DIR=$$PWD/build/debug/dist/lib/cmake/niu2x \
		-Dniu2x_core_DIR=$$PWD/build/debug/dist/lib/cmake/niu2x \
		-Dniu2x_image_DIR=$$PWD/build/debug/dist/lib/cmake/niu2x \
		-Dniu2x_painter_DIR=$$PWD/build/debug/dist/lib/cmake/niu2x \
		-Dniu2x_math_DIR=$$PWD/build/debug/dist/lib/cmake/niu2x \
		-DCMAKE_BUILD_TYPE=Debug;
	cmake --build build/test-app-static/debug -j


.PHONY: 
