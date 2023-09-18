all: build-library build-app

build-library: build-shared-library build-static-library

build-shared-library:
	cmake -S. \
		-Bbuild-shared \
		-DBUILD_SHARED_LIBS=ON \
		-DCMAKE_BUILD_TYPE=Release;
	cmake --build build-shared;
	cmake --install build-shared --prefix dist-shared;

build-static-library:
	cmake -S. \
		-Bbuild-static \
		-DBUILD_SHARED_LIBS=OFF \
		-DCMAKE_BUILD_TYPE=Release;
	cmake --build build-static;
	cmake --install build-static --prefix dist-static;

build-app:
	cmake -S app -Bbuild-app \
		-Dniu2x_filesystem_DIR=$$PWD/dist-static/lib/cmake/niu2x \
		-Dniu2x_core_DIR=$$PWD/dist-static/lib/cmake/niu2x
	cmake --build build-app

.PHONY: 
