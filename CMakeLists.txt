cmake_minimum_required(VERSION 3.15)
project(Specto VERSION 0.1 LANGUAGES CXX)

# ==== START set misc options
set(OUTDIR ${CMAKE_CURRENT_BINARY_DIR}/out)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTDIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTDIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTDIR}/bin)

# Useful for certain IDEs' intellisense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# ==== END set misc options

# ==== START Conan Deps
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(FFTW3f REQUIRED)
find_package(audiofile REQUIRED)
# Test requires
find_package(GTest REQUIRED)
# ==== END Conan Deps

# ==== START specto lib definition
set(SPECTO_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SPECTO_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
file(GLOB SPECTO_SOURCES "src/*.cc")

add_library(specto SHARED ${SPECTO_SOURCES})
add_library(specto_static STATIC ${SPECTO_SOURCES})

# Set props for static and shared specto lib
foreach(SPECTO_TARGET specto specto_static)
    target_include_directories(${SPECTO_TARGET} PUBLIC ${SPECTO_INC_DIR})
    target_include_directories(${SPECTO_TARGET} PRIVATE ${SPECTO_SRC_DIR})

    target_link_libraries(${SPECTO_TARGET} FFTW3::fftw3f)
    target_include_directories(${SPECTO_TARGET} PRIVATE ${FFTW3f_INCLUDE_DIRS})

    target_link_libraries(${SPECTO_TARGET} audiofile::audiofile)
endforeach()
# ==== END specto lib definition

# ==== START example executable
set(EXAMPLE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/example)
file(GLOB EXAMPLE_SOURCES "${EXAMPLE_DIR}/src/*.cc")
add_executable(specto_example ${EXAMPLE_SOURCES})
# Change library to specto instead of specto_static to use shared lib
target_link_libraries(specto_example specto_static)
target_link_libraries(specto_example SDL2::SDL2)
target_link_libraries(specto_example sdl_ttf::sdl_ttf)
target_include_directories(specto_example PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(specto_example PRIVATE ${sdl_ttf_INCLUDE_DIRS})
target_link_libraries(specto_example audiofile::audiofile)
# ==== END example executable

# ==== START run example target
set(SONG_PATH ${EXAMPLE_DIR}/res/TaylorSwift_IKnewYouWereTrouble_FullSong.wav)
# Uncomment to use a different wav file
# set(SONG_PATH ${EXAMPLE_DIR}/res/notes1.wav)
set(TTF_PATH ${EXAMPLE_DIR}/res/arial_unicode.ttf)
add_custom_target(
        specto_example_run
        COMMAND specto_example ${SONG_PATH} ${TTF_PATH}
        WORKING_DIRECTORY ${CMAKE_PROJECT_DIR})
# ==== END run example target

# ==== START specto unit tests
set(SPECTO_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(SPECTO_TEST_SRC_DIR ${SPECTO_TEST_DIR}/src)
file(GLOB SPECTO_TEST_SOURCES "${SPECTO_TEST_SRC_DIR}/*.cc")
add_executable(specto_test ${SPECTO_TEST_SOURCES})
target_include_directories(specto_test PRIVATE ${SPECTO_TEST_SRC_DIR})
target_link_libraries(specto_test specto_static)
# Include specto private headers for unit testing
target_include_directories(specto_test PRIVATE ${SPECTO_SRC_DIR})
target_link_libraries(specto_test GTest::GTest)
target_include_directories(specto_test PRIVATE ${GTest_INCLUDE_DIRS})
# ==== END specto unit tests

# ==== START run specto unit tests target
add_custom_target(
        specto_test_run
        COMMAND specto_test
        WORKING_DIRECTORY ${CMAKE_PROJECT_DIR})
# ==== END run specto unit tests target