project(Engine CXX C)

file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp)
file(GLOB_RECURSE PROJECT_HEADERS include/*.h)
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/vendor/imgui)
file(GLOB_RECURSE VENDOR_SOURCES
        ${CMAKE_SOURCE_DIR}/vendor/glad/*.c
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)


set_source_files_properties(${VENDOR_SOURCES} PROPERTIES SKIP_PRECOMPILE_HEADERS ON)

add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${VENDOR_SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE IMGUI_IMPL_GLFW_DISABLE_X11)

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
        ${CMAKE_SOURCE_DIR}/vendor/spdlog/include/
        ${CMAKE_SOURCE_DIR}/vendor/glfw/include/
        ${CMAKE_SOURCE_DIR}/vendor/glad/include/
        ${CMAKE_SOURCE_DIR}/vendor/imgui/
        ${CMAKE_SOURCE_DIR}/vendor/imgui/backends/
)

target_link_libraries(Engine PRIVATE glfw)

if(WIN32)
    target_link_libraries(Engine PRIVATE dwmapi)
endif()

target_precompile_headers(
        ${PROJECT_NAME}
        PRIVATE
        include/weave/PCH.h
)
