all: build-shared-library build-static-library

build-shared-library:
	cmake -S. \
		-Bbuild-shared \
		-DNXC_BUILD_TEST=ON \
		-DBUILD_SHARED_LIBS=ON \
		-DCMAKE_BUILD_TYPE=debug;
	cmake --build build-shared

build-static-library:
	cmake -S. \
		-Bbuild-static \
		-DNXC_BUILD_TEST=ON \
		-DBUILD_SHARED_LIBS=OFF \
		-DCMAKE_BUILD_TYPE=debug;
	cmake --build build-static

.PHONY: 
