cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

project(Game)

file(GLOB_RECURSE CPP_FILES "src/*.cpp")
file(COPY "src/shaders" DESTINATION ".")


add_executable(${PROJECT_NAME} ${CPP_FILES})

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)


add_subdirectory(external/glm)
target_link_libraries(${PROJECT_NAME} PRIVATE glm)