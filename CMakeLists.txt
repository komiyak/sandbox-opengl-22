cmake_minimum_required(VERSION 3.22)
project(sandbox_opengl_22)

set(CMAKE_CXX_STANDARD 17)


add_subdirectory(
        external_lib/glfw-3.3.8
        external_lib/glfw-3.3.8-build)
add_library(glad STATIC external_lib/glad-opengl-version-4-5/src/glad.c)

# Add glm library
include(FetchContent)
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 0.9.9.8)
FetchContent_MakeAvailable(glm)


include_directories(
        external_lib/glfw-3.3.8/include
        external_lib/glad-opengl-version-4-5/include
        ${glm_SOURCE_DIR})

add_executable(
        sandbox_opengl_22
        main.cpp
        vertex_render_object.cpp
        shader.cpp
        fps.cpp
        png_load.cpp)

target_link_libraries(
        sandbox_opengl_22
        glfw
        glad
        png)


# Coping resource files into the build dir.
file(INSTALL shader DESTINATION "${CMAKE_BINARY_DIR}")
