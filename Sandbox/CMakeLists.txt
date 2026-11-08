project(Sandbox CXX)

file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp)
file(GLOB_RECURSE PROJECT_HEADERS include/*.h)
set(PROJECT_RC ${CMAKE_SOURCE_DIR}/app.rc)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${PROJECT_RC})

target_compile_definitions(${PROJECT_NAME} PRIVATE ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets")

target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

target_link_libraries(${PROJECT_NAME} Engine)
