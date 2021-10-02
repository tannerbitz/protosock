cmake_minimum_required(VERSION 3.13)

project(protosock VERSION 1.0
                  LANGUAGES CXX
                  DESCRIPTION "Project sending protobuf messages over sockets")

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
# find external libraries
find_package(cppzmq REQUIRED)
find_package(GTest REQUIRED)
find_package(Protobuf REQUIRED)


# add local libraries
add_subdirectory(Libraries)
add_subdirectory(Binaries)
