# Specto

A C++ library which draws a spectogram into an SDL window for a WAV file.

# Install

Git clone this repo then

If you don't have conan:
```
$ pip install conan
```

Also install cmake if you don't have it!
```
$ brew install cmake
```

Then:
```
$ conan install . --output-folder=./build --build=missing
$ cd build
$ cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
$ cmake --build .
```