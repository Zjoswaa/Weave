cmake_minimum_required(VERSION 3.10)
project(Weave)
set(CMAKE_CXX_STANDARD 23)

# Detect platform
if (WIN32)
    add_compile_definitions(WEAVE_PLATFORM_WINDOWS)
elseif (UNIX AND NOT APPLE)
    add_compile_definitions(WEAVE_PLATFORM_LINUX)
else ()
    message(FATAL_ERROR "Invalid platform, only Windows and Linux (non-Apple) are supported")
endif ()

get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

if (IS_MULTI_CONFIG)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
else ()
    if (NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
    endif ()
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")

    if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug" AND NOT CMAKE_BUILD_TYPE STREQUAL "Release")
        message(FATAL_ERROR "Undefined or invalid build configuration: ${CMAKE_BUILD_TYPE}")
    endif ()
endif ()

add_compile_definitions(
        $<$<CONFIG:Debug>:WEAVE_DEBUG>
        $<$<CONFIG:Release>:WEAVE_RELEASE>
)
set(CMAKE_VERBOSE_MAKEFILE $<CONFIG:Debug>)

# Detect compiler
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_definitions(WEAVE_COMPILER_CLANG)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_definitions(WEAVE_COMPILER_GCC)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_definitions(WEAVE_COMPILER_MSVC)
    add_compile_options(/utf-8)
else ()
    message(FATAL_ERROR "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")
endif ()

# CMake flags
option(WEAVE_ENABLE_ASSERTS "Enable Weave asserts" OFF)
if (WEAVE_ENABLE_ASSERTS)
    add_compile_definitions(WEAVE_ENABLE_ASSERTS)
endif ()

add_subdirectory(vendor/spdlog)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_X11 OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/glfw)

add_subdirectory(Engine)
add_subdirectory(Sandbox)
