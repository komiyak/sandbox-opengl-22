cmake_minimum_required(VERSION 3.22)
project(sandbox_opengl_22)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(
        external_lib/glfw-3.3.8
        external_lib/glfw-3.3.8-build)
add_library(glad STATIC external_lib/glad-opengl-version-4-5/src/glad.c)

include_directories(
        external_lib/glfw-3.3.8/include
        external_lib/glad-opengl-version-4-5/include)

add_executable(
        sandbox_opengl_22
        main.cpp)

target_link_libraries(
        sandbox_opengl_22
        glfw
        glad)

# Coping resource files into the build dir.
file(COPY shader DESTINATION "${CMAKE_BINARY_DIR}")
