#ifndef WEAVE_VERSION_H
#define WEAVE_VERSION_H

#define WEAVE_VERSION "0.1.0-a.1"

// == Platform ==
#ifdef WEAVE_PLATFORM_WINDOWS
    #define WEAVE_PLATFORM_NAME "Windows"
#elifdef WEAVE_PLATFORM_LINUX
    #define WEAVE_PLATFORM_NAME "Linux"
#else
    #define WEAVE_PLATFORM_NAME "Unknown"
#endif

// == Build configuration ==
#ifdef WEAVE_DEBUG
    #define WEAVE_BUILD_CONFIG_NAME "Debug"
#elifdef WEAVE_RELEASE
    #define WEAVE_BUILD_CONFIG_NAME "Release"
#else
    #define WEAVE_BUILD_CONFIG_NAME "Unknown"
#endif

// == Compiler ==
#ifdef WEAVE_COMPILER_CLANG
    #define WEAVE_COMPILER_NAME "Clang"
#elifdef WEAVE_COMPILER_GCC
    #define WEAVE_COMPILER_NAME "GCC"
#elifdef WEAVE_COMPILER_MSVC
    #define WEAVE_COMPILER_NAME "MSVC"
#else
    #define WEAVE_COMPILER_NAME "Unknown"
#endif

#define WEAVE_VERSION_FULL WEAVE_VERSION " (" WEAVE_PLATFORM_NAME " - " WEAVE_BUILD_CONFIG_NAME " - " WEAVE_COMPILER_NAME ")"

#endif
