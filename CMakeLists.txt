cmake_minimum_required(VERSION 4.4)
set(CMAKE_CXX_STANDARD 23)
project(Weave)

# Detect platform
if(WIN32)
    add_compile_definitions(WEAVE_PLATFORM_WINDOWS)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    add_compile_definitions(NOMINMAX)
elseif(UNIX AND NOT APPLE)
    add_compile_definitions(WEAVE_PLATFORM_LINUX)
else()
    message(FATAL_ERROR "Invalid platform, only Windows and Linux (non-Apple) are supported")
endif()

get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

if(IS_MULTI_CONFIG)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
else()
    if (NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
    endif()
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")

    if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug" AND NOT CMAKE_BUILD_TYPE STREQUAL "Release")
        message(FATAL_ERROR "Undefined or invalid build configuration: ${CMAKE_BUILD_TYPE}")
    endif()
endif()

add_compile_definitions(
        $<$<CONFIG:Debug>:WEAVE_DEBUG>
        $<$<CONFIG:Release>:WEAVE_RELEASE>
)
set(CMAKE_VERBOSE_MAKEFILE $<CONFIG:Debug>)

# Detect compiler
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_definitions(WEAVE_COMPILER_CLANG)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_definitions(WEAVE_COMPILER_GCC)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_definitions(WEAVE_COMPILER_MSVC)
    add_compile_options(/utf-8)
else()
    message(FATAL_ERROR "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

# CMake flags
option(WEAVE_ENABLE_ASSERTS "Enable Weave asserts" OFF)
if(WEAVE_ENABLE_ASSERTS)
    add_compile_definitions(WEAVE_ENABLE_ASSERTS)
endif()

# Windowing backend
set(WEAVE_WINDOWING_BACKEND "GLFW" CACHE STRING "The windowing backend to use, available options: 'GLFW'")
if (WEAVE_WINDOWING_BACKEND STREQUAL "GLFW")
    add_compile_definitions(WEAVE_WINDOWING_BACKEND_GLFW)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_X11 OFF CACHE BOOL "" FORCE)
    add_subdirectory(deps/glfw)
else()
    message(FATAL_ERROR "Undefined or invalid windowing backend: ${WEAVE_WINDOWING_BACKEND}")
endif()

# Rendering backend
option(WEAVE_RENDERING_OPENGL "Build the OpenGL backend" ON)
#option(WEAVE_RENDERING_VULKAN "Build the Vulkan backend" OFF)
if (NOT WEAVE_RENDERING_OPENGL)
    message(FATAL_ERROR "No rendering backend enabled")
endif()
if (WEAVE_RENDERING_OPENGL)
    add_compile_definitions(WEAVE_HAS_OPENGL)
endif()

add_subdirectory(deps)
add_subdirectory(Engine)
add_subdirectory(Sandbox)
