cmake_minimum_required(VERSION 3.0)

project(toy_compiler VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(
    SOURCES
    src/tokens.cpp
    src/main.cpp
)

add_executable(compiler ${SOURCES})

target_include_directories(compiler PUBLIC "build" "include")

