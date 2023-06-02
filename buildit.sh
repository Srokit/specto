#!/bin/sh

# Run this script to build using conan and cmake

conan install . --output-folder=./build --build=missing
pushd ./build
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .
popd
