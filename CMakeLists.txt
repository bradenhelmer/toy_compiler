cmake_minimum_required(VERSION 3.0)

project(toy_compiler VERSION 0.0.1)


find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

llvm_map_components_to_libnames(LLVM_LIBS core support irreader)

message(STATUS "Components mapped to libnames: ${llvm_libs}")

set(
    SOURCES
    src/utils.cpp
    src/tokens.cpp
    src/lexer.cpp
    src/main.cpp
)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Build Target
add_executable(compiler ${SOURCES})
target_include_directories(compiler PUBLIC "build" "include")
target_link_libraries(compiler PUBLIC ${LLVM_LIBS})
add_custom_target(test COMMAND ./compiler)


