if(WEAVE_RENDERING_OPENGL)
    add_subdirectory(glad.cmake)
endif()

set(GLM_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLM_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
add_subdirectory(glm)

add_subdirectory(imgui.cmake)

set(SPDLOG_BUILD_EXAMPLE OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(spdlog)
