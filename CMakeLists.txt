cmake_minimum_required(VERSION 3.22)
project(sandbox_opengl_22)

set(CMAKE_CXX_STANDARD 17)

# デバッグ時にエラー位置の特定のために backtrace_symbols() を利用するとき、
# アドレスと一緒に関数名を表示するために有効にしている。
# 必要がない場合は OFF にするべきらしい。簡易的な stacktrace 取得のために使用。
# Note: デバッグ用のスタックトレース実装は自分で作る必要があるかもしれない。
# Ref: https://gcc.gnu.org/onlinedocs/gcc-9.1.0/gcc/Link-Options.html#index-rdynamic
set(CMAKE_CXX_FLAGS -rdynamic)


add_subdirectory(glfw_wrap)
add_subdirectory(gl_app)
#add_subdirectory(google_tests)


# Add glm library
include(FetchContent)

# glm that is a math library for OpenGL.
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 0.9.9.8)
FetchContent_MakeAvailable(glm)

# assimp that is 3D model importer library.
FetchContent_Declare(
        assimp
        GIT_REPOSITORY git@github.com:assimp/assimp.git
        GIT_TAG v5.2.5)
FetchContent_MakeAvailable(assimp)

include_directories(
        ${glm_SOURCE_DIR}
        ${assimp_SOURCE_DIR})


add_executable(
        sandbox_opengl_22
        main.cpp
        vertex_render_object.cpp
        shader.cpp
        shader_uniform/shader_uniform.cpp
        shader_uniform/basic_shader_uniform.cpp
        shader_uniform/texture_shader_uniform.cpp
        shader_uniform/texture_2d_shader_uniform.cpp
        shader_uniform/font_shader_uniform.cpp
        shader_uniform/practice_lighting_phong_shading_shader_uniform.cpp
        shader_uniform/practice_lighting_lighting_map_shader_uniform.cpp
        shader_uniform/learnopengl_lighting_directional_light_shader_uniform.cpp
        shader_uniform/learnopengl_lighting_multiple_lights_shader_uniform.cpp
        shader_uniform/learnopengl_lighting_point_light_shader_uniform.cpp
        shader_uniform/learnopengl_lighting_spotlight_shader_uniform.cpp
        bitmap_font_render.cpp
        png_load.cpp
        game_math.cpp
        vertex_specification/vertex_specification.cpp
        vertex_specification/position_vertex_specification.cpp
        vertex_specification/position_with_normal_vector_vertex_specification.cpp
        vertex_specification/position_with_normal_and_texcoord_vertex_specification.cpp
        vertex_specification/position_and_normal_and_texcoord_vertex_specification.cpp
        vertex_specification/color_vertex_specification.cpp
        vertex_specification/texture_vertex_specification.cpp
        vertex_specification/texture_2d_vertex_specification.cpp
        cstring_util.cpp
        texture.cpp
        scene/starting_scene.cpp
        scene/sandbox_scene.cpp
        scene/learn_open_gl_lighting_scene.cpp
        scene/learn_open_gl_lighting_light_casters_scene.cpp
        scene/learn_open_gl_lighting_multiple_lights_scene.cpp
        assimp_mesh.cpp)

target_link_libraries(
        sandbox_opengl_22
        LINK_PUBLIC
        assimp
        gl_app
        png)


# Copy updated shader files and texture files to the binary directory when the project is built.
# See: https://stackoverflow.com/a/34800230
add_custom_command(
        TARGET sandbox_opengl_22 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/shader/*.* ${CMAKE_CURRENT_BINARY_DIR}/shader)
add_custom_command(
        TARGET sandbox_opengl_22 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/texture/*.* ${CMAKE_CURRENT_BINARY_DIR}/texture)
