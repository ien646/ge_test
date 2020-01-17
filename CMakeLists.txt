cmake_minimum_required(VERSION 3.0.0)
project(graphext_test LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_executable(graphext_test
    src/crossFilter.cpp
    src/csvReader.cpp
    src/main.cpp
    src/stringUtils.cpp)

target_include_directories(graphext_test PRIVATE include)