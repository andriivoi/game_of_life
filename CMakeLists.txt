cmake_minimum_required(VERSION 2.8.12)

project(cm_game_of_life)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_internal")

set(CMAKE_BINARY_DIR         ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH   ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH      ${CMAKE_BINARY_DIR}/lib)
set(UNIT_TEST_BIN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin_tests)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

option(BUILD_SHARED_LIBS "Flag to cause add_library to create shared libraries if ON." ON)

add_subdirectory(src/app)
add_subdirectory(src/game_of_life_engine)
add_subdirectory(src/tests)
