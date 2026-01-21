project(Sandbox CXX)

file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} Engine)
