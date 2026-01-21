cmake_minimum_required(VERSION 3.10)
project(Weave)
set(CMAKE_CXX_STANDARD 20)

# Detect platform
if (WIN32)
    add_compile_definitions(WEAVE_PLATFORM_WINDOWS)
elseif (UNIX AND NOT APPLE)
    add_compile_definitions(WEAVE_PLATFORM_LINUX)
else()
    message(FATAL_ERROR "Invalid platform, only Windows and Linux (non-Apple) are supported")
endif()

# Detect build configuration
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_VERBOSE_MAKEFILE 1)
    add_compile_definitions(WEAVE_DEBUG)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_VERBOSE_MAKEFILE 0)
    add_compile_definitions(WEAVE_RELEASE)
else()
    message(FATAL_ERROR "Undefined or invalid build configuration")
endif()

# Detect compiler
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_definitions(WEAVE_COMPILER_CLANG)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_definitions(WEAVE_COMPILER_GCC)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_definitions(WEAVE_COMPILER_MSVC)
    add_compile_options(/utf-8)
else()
    add_compile_definitions(WEAVE_COMPILER_UNKNOWN)
endif()

# CMake flags
option(WEAVE_ENABLE_ASSERTS "Enable Weave asserts" OFF)
if (WEAVE_ENABLE_ASSERTS)
    add_compile_definitions(WEAVE_ENABLE_ASSERTS)
endif()

add_subdirectory(vendor/spdlog)

add_subdirectory(Engine)
add_subdirectory(Sandbox)
