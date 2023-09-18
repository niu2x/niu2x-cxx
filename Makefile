all: build-library

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

.PHONY: 
