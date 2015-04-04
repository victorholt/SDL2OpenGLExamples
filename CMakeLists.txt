cmake_minimum_required(VERSION 3.2)

# CMake file for compiling our sources

# Environment settings
include (cmake/env.cmake)

# Project include directories
include (cmake/include_dir.cmake)

# External libraries
include (cmake/linked_libraries.cmake)

# Target files to build
include (cmake/target.cmake)