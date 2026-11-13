set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../imgui)

add_library(imgui STATIC
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
)

target_include_directories(imgui SYSTEM PUBLIC ${IMGUI_DIR})

if (WEAVE_WINDOWING_BACKEND STREQUAL "GLFW")
    target_sources(imgui PRIVATE ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp)
    target_include_directories(imgui SYSTEM PUBLIC ${IMGUI_DIR}/backends)
    target_link_libraries(imgui PUBLIC glfw)
endif()

if (WEAVE_RENDERING_OPENGL)
    target_sources(imgui PRIVATE ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp)
    target_include_directories(imgui SYSTEM PUBLIC ${IMGUI_DIR}/backends)
endif()
