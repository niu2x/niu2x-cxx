LIB_DEBUG_BUILD := build/debug
LIB_RELEASE_BUILD := build/release

LIB_DEBUG_DIST := dist/debug
LIB_RELEASE_DIST := dist/release

LIB_DIR := $(PWD)/$(LIB_RELEASE_DIST)/lib/cmake/niu2x

all: release-library

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


# build app
.PHONY: library \
		debug-library \
		release-library 