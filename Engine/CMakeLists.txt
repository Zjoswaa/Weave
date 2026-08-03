project(Engine CXX)

file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp)
file(GLOB_RECURSE PROJECT_HEADERS include/*.h)
file(GLOB_RECURSE VENDOR_SOURCES vendor/glad/*.c)

add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES} ${PROJECT_HEADERS})

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
        ${CMAKE_SOURCE_DIR}/vendor/spdlog/include/
        ${CMAKE_SOURCE_DIR}/vendor/glfw/include/
        ${CMAKE_SOURCE_DIR}/vendor/glad/include/
)

target_link_libraries(Engine PRIVATE glfw)

target_precompile_headers(
        ${PROJECT_NAME}
        PRIVATE
        include/weave/PCH.h
)
