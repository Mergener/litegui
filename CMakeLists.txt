cmake_minimum_required(VERSION 3.24)
project(litegui)

enable_testing()

set(CMAKE_CXX_STANDARD 17)

set(SRC_DIRECTORY ${CMAKE_SOURCE_DIR}/src)
set(EXT_DIRECTORY ${CMAKE_SOURCE_DIR}/ext)

add_subdirectory(ext)
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(examples)