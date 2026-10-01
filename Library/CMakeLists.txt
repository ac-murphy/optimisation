cmake_minimum_required(VERSION 4.1)
project(LibraryProject DESCRIPTION "Optimisation techniques library.")

set(CMAKE_VERBOSE_MAKEFILE ON)

add_library(LibraryProject tmp.cpp
        Library/matrix.h)