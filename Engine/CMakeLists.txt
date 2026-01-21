project(Engine CXX)

file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp)
file(GLOB_RECURSE PROJECT_HEADERS include/*.h)

add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES} ${PROJECT_HEADERS})

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ${CMAKE_SOURCE_DIR}/vendor/spdlog/include/
)

target_precompile_headers(
        ${PROJECT_NAME}
        PRIVATE
        include/Weave/PCH.h
)
