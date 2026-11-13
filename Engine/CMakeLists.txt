project(Engine CXX C)

file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp)
file(GLOB_RECURSE PROJECT_HEADERS include/*.h)

if (WEAVE_RENDERING_OPENGL)
    file(GLOB_RECURSE GLAD_SOURCES ${CMAKE_SOURCE_DIR}/deps/glad/*.c)
    set_source_files_properties(${GLAD_SOURCES} PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
endif()

add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${GLAD_SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets")

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
        ${CMAKE_SOURCE_DIR}/deps/spdlog/include/
)

if (WEAVE_WINDOWING_BACKEND STREQUAL "GLFW")
    target_include_directories(
            ${PROJECT_NAME}
            PUBLIC
            ${CMAKE_SOURCE_DIR}/deps/glfw/include/
    )

    target_link_libraries(Engine PRIVATE glfw)
endif()

if (WEAVE_RENDERING_OPENGL)
    target_include_directories(
            ${PROJECT_NAME}
            PUBLIC
            ${CMAKE_SOURCE_DIR}/deps/glad/include/
    )
endif()

if(WIN32)
    target_link_libraries(Engine PRIVATE dwmapi)
endif()

target_precompile_headers(
        ${PROJECT_NAME}
        PRIVATE
        include/weave/PCH.h
)
