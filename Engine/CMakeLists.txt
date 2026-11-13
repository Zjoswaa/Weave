project(Engine CXX C)

file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS
        src/core/*.cpp
        src/platform/platform.cpp
        src/renderer/*.cpp
)
file(GLOB_RECURSE CORE_HEADERS CONFIGURE_DEPENDS
        include/weave/entry_point.h
        include/weave.h
        include/weave/core/*.h
        include/weave/platform/platform.h
        include/weave/renderer/*.h
)

add_library(${PROJECT_NAME} STATIC ${CORE_SOURCES} ${CORE_HEADERS})

if (WEAVE_WINDOWING_BACKEND STREQUAL "GLFW")
    file(GLOB_RECURSE GLFW_SOURCES CONFIGURE_DEPENDS include/weave/platform/glfw/*.h)
    file(GLOB_RECURSE GLFW_HEADERS CONFIGURE_DEPENDS src/platform/glfw/*.cpp)
    target_sources(${PROJECT_NAME} PRIVATE ${GLFW_SOURCES} ${GLFW_HEADERS})
    target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../deps/glfw/include/)
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
endif()

if (WEAVE_RENDERING_OPENGL)
    file(GLOB_RECURSE OPENGL_SOURCES CONFIGURE_DEPENDS src/platform/opengl/*.cpp)
    file(GLOB_RECURSE OPENGL_HEADERS CONFIGURE_DEPENDS include/weave/platform/opengl/*.h)
    target_sources(${PROJECT_NAME} PRIVATE ${OPENGL_SOURCES} ${OPENGL_HEADERS})
    target_link_libraries(${PROJECT_NAME} PRIVATE glad)
endif()

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE dwmapi)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE ASSETS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../assets")

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

target_link_libraries(${PROJECT_NAME}
        PUBLIC spdlog::spdlog
        PRIVATE imgui
)

target_precompile_headers(
        ${PROJECT_NAME}
        PRIVATE
        include/weave/PCH.h
)
