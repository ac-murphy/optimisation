cmake_minimum_required(VERSION 4.1)
project(TestingProject DESCRIPTION "Optimisation techniques library testing.")

# GTest.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_subdirectory(${PROJECT_SOURCE_DIR}/Dependencies/GTest/googletest-1.17.0 EXCLUDE_FROM_ALL)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_executable(TestingProject UnitTest.cpp
        ../Library/tmp.cpp
        ../Library/tmp.h)

target_include_directories(TestingProject PRIVATE
        ${PROJECT_SOURCE_DIR}/
        ${PROJECT_SOURCE_DIR}/Dependencies
        ${PROJECT_SOURCE_DIR}/Dependencies/GTest/googletest-1.17.0/googletest/include
)
target_compile_definitions(TestingProject PRIVATE
        TEST_RESOURCE_DIR="${PROJECT_SOURCE_DIR}/TestData/"
)
target_link_libraries(TestingProject gtest gtest_main)
target_link_libraries(TestingProject LibraryProject)