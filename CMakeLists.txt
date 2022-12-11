cmake_minimum_required(VERSION 3.22)
project(sandbox_opengl_22)

set(CMAKE_CXX_STANDARD 17)

# デバッグ時にエラー位置の特定のために backtrace_symbols() を利用するとき、
# アドレスと一緒に関数名を表示するために有効にしている。
# 必要がない場合は OFF にするべきらしい。簡易的な stacktrace 取得のために使用。
# Note: デバッグ用のスタックトレース実装は自分で作る必要があるかもしれない。
# Ref: https://gcc.gnu.org/onlinedocs/gcc-9.1.0/gcc/Link-Options.html#index-rdynamic
set(CMAKE_CXX_FLAGS -rdynamic)


add_subdirectory(
        external_lib/glfw-3.3.8
        external_lib/glfw-3.3.8-build)
add_library(glad STATIC external_lib/glad-opengl-version-4-6/src/glad.c)

# Add glm library
include(FetchContent)
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 0.9.9.8)
FetchContent_MakeAvailable(glm)


include_directories(
        external_lib/glfw-3.3.8/include
        external_lib/glad-opengl-version-4-6/include
        ${glm_SOURCE_DIR})

add_executable(
        sandbox_opengl_22
        main.cpp
        vertex_render_object.cpp
        shader.cpp
        basic_shader_uniform.cpp
        texture_shader_uniform.cpp
        texture_2d_shader_uniform.cpp
        font_shader_uniform.cpp
        practice_lighting_phong_shading_shader_uniform.cpp
        practice_lighting_lighting_map_shader_uniform.cpp
        bitmap_font_render.cpp
        frame.cpp
        png_load.cpp
        game_math.cpp
        position_vertex_specification.cpp
        position_with_normal_vector_vertex_specification.cpp
        position_with_normal_and_texcoord_vertex_specification.cpp
        color_vertex_specification.cpp
        texture_vertex_specification.cpp
        texture_2d_vertex_specification.cpp
        opengl_debug.cpp
        cstring_util.cpp
        key_callback_singleton.cpp
        basic_sample_activity.cpp
        lighting_example_activity.cpp
        main_activity.cpp
        application.cpp)

target_link_libraries(
        sandbox_opengl_22
        glfw
        glad
        png)

add_subdirectory(google_tests)

# Coping resource files into the build dir.
file(INSTALL shader DESTINATION "${CMAKE_BINARY_DIR}")
file(INSTALL texture DESTINATION "${CMAKE_BINARY_DIR}")
