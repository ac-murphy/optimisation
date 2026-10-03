cmake_minimum_required(VERSION 4.1)
project(LibraryProject DESCRIPTION "Optimisation techniques library.")

set(CMAKE_VERBOSE_MAKEFILE ON)

add_library(LibraryProject tmp.cpp)

target_include_directories(LibraryProject PUBLIC
        ${PROJECT_SOURCE_DIR}/Library
)