project(Engine CXX C)

file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp)
file(GLOB_RECURSE PROJECT_HEADERS include/*.h)
file(GLOB_RECURSE VENDOR_SOURCES ${CMAKE_SOURCE_DIR}/vendor/glad/*.c)

set_source_files_properties(${VENDOR_SOURCES} PROPERTIES SKIP_PRECOMPILE_HEADERS ON)

add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${VENDOR_SOURCES})

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
