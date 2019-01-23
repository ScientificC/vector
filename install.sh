#!/bin/bash

pushd `pwd`

rm -rf build
mkdir build
cd build

cmake -G "Unix Makefiles" .. -DVECTOR_BUILD_STATIC=ON -DVECTOR_BUILD_SHARED=ON && \
	make && \
	ctest && \
	sudo make install

popd
