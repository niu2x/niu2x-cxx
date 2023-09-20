all: build-library build-test-app

build-library: build-debug-shared-library \
				build-debug-static-library \
				build-release-shared-library \
				build-release-static-library

build-debug-shared-library:
	cmake -S. \
		-Bbuild/shared/debug \
		-DBUILD_SHARED_LIBS=ON \
		-DCMAKE_BUILD_TYPE=Debug;
	cmake --build build/shared/debug -j2;
	cmake --install build/shared/debug --prefix build/shared/debug/dist;

build-debug-static-library:
	cmake -S. \
		-Bbuild/static/debug \
		-DBUILD_SHARED_LIBS=OFF \
		-DCMAKE_BUILD_TYPE=Debug;
	cmake --build build/static/debug -j2;
	cmake --install build/static/debug --prefix build/static/debug/dist/

build-release-shared-library:
	cmake -S. \
		-Bbuild/shared/release \
		-DBUILD_SHARED_LIBS=ON \
		-DCMAKE_BUILD_TYPE=Release;
	cmake --build build/shared/release -j2;
	cmake --install build/shared/release --prefix build/shared/release/dist;

build-release-static-library:
	cmake -S. \
		-Bbuild/static/release \
		-DBUILD_SHARED_LIBS=OFF \
		-DCMAKE_BUILD_TYPE=Release;
	cmake --build build/static/release -j2;
	cmake --install build/static/release --prefix build/static/release/dist/

build-test-app:
	cmake -S test-app -Bbuild-test-app-static \
		-Dniu2x_filesystem_DIR=$$PWD/build/static/debug/dist/lib/cmake/niu2x \
		-Dniu2x_stream_DIR=$$PWD/build/static/debug/dist/lib/cmake/niu2x \
		-Dniu2x_crypto_DIR=$$PWD/build/static/debug/dist/lib/cmake/niu2x \
		-Dniu2x_core_DIR=$$PWD/build/static/debug/dist/lib/cmake/niu2x
	cmake --build build-test-app-static


.PHONY: 
