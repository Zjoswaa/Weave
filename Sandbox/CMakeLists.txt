project(Sandbox CXX)

file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp)
file(GLOB_RECURSE PROJECT_HEADERS include/*.h)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})

target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

target_link_libraries(${PROJECT_NAME} Engine)
