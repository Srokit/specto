cmake_minimum_required(VERSION 3.15)
project(Specto)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCES "src/*.cc")

include_directories(inc)
add_library(specto SHARED ${SOURCES})

add_executable(specto_test test/main.cc)
target_link_libraries(specto_test specto)

include(FindPkgConfig)
pkg_check_modules(fftw3 REQUIRED IMPORTED_TARGET fftw3f)
target_link_libraries(specto PkgConfig::fftw3)

# Conan
find_package(sdl2 REQUIRED)
target_link_libraries(specto SDL2::SDL2)
target_include_directories(specto PRIVATE ${SDL2_INCLUDE_DIRS})

set(AUDIO_FILE_H_PATH ${CMAKE_CURRENT_BINARY_DIR}/inc/AudioFile.h)
# Load audiofile single file header
if (NOT EXISTS ${AUDIO_FILE_H_PATH})
    message(STATUS "Downloading AudioFile.h")
    file(DOWNLOAD https://raw.githubusercontent.com/adamstark/AudioFile/master/AudioFile.h ${AUDIO_FILE_H_PATH})
endif()
target_include_directories(specto PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/inc)

set(SONG_PATH ${CMAKE_CURRENT_SOURCE_DIR}/test/TaylorSwift_IKnewYouWereTrouble_FullSong.wav)
add_custom_target(
        specto_test_run
        COMMAND specto_test ${SONG_PATH}
        DEPENDS specto_test
        WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)