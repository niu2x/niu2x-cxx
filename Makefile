all: build-library build-test-app

build-library: build-shared-library build-static-library

build-shared-library:
	cmake -S. \
		-Bbuild-shared \
		-DBUILD_SHARED_LIBS=ON \
		-DCMAKE_BUILD_TYPE=Debug;
	cmake --build build-shared -j2;
	cmake --install build-shared --prefix build-shared/dist;

build-static-library:
	cmake -S. \
		-Bbuild-static \
		-DBUILD_SHARED_LIBS=OFF \
		-DCMAKE_BUILD_TYPE=Debug;
	cmake --build build-static -j2;
	cmake --install build-static --prefix build-static/dist/

build-test-app:
	cmake -S test-app -Bbuild-test-app-static \
		-Dniu2x_filesystem_DIR=$$PWD/build-static/dist/lib/cmake/niu2x \
		-Dniu2x_stream_DIR=$$PWD/build-static/dist/lib/cmake/niu2x \
		-Dniu2x_core_DIR=$$PWD/build-static/dist/lib/cmake/niu2x
	cmake --build build-test-app-static

.PHONY: 
