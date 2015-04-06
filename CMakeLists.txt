cmake_minimum_required(VERSION 3.1)
# CMake file for compiling our sources

add_definitions(-DSDL_MAIN_NEEDED)

# Environment settings
include (cmake/env.cmake)

# Project include directories
include (cmake/include_dir.cmake)

# External libraries
include (cmake/linked_libraries.cmake)

# Target files to build
include (cmake/target.cmake)
