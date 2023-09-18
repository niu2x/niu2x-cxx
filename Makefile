all: test

build-shared-library:
	cmake -S. \
		-Bbuild-shared \
		-DNXC_BUILD_TEST=ON \
		-DBUILD_SHARED_LIBS=ON \
		-DCMAKE_BUILD_TYPE=Debug;
	cmake --build build-shared;

build-static-library:
	cmake -S. \
		-Bbuild-static \
		-DNXC_BUILD_TEST=ON \
		-DBUILD_SHARED_LIBS=OFF \
		-DCMAKE_BUILD_TYPE=Debug;
	cmake --build build-static;

test: build-shared-library build-static-library
# 	cd build-shared && ctest;
# 	cd build-static && ctest;

.PHONY: 
