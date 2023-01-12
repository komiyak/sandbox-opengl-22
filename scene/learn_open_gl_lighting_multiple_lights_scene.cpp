#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "learn_open_gl_lighting_multiple_lights_scene.h"
#include "../application/application.h"
#include "../shader.h"
#include "../vertex_render_object.h"
#include "../shader_uniform/basic_shader_uniform.h"
#include "../shader_uniform/practice_lighting_phong_shading_shader_uniform.h"
#include "../shader_uniform/practice_lighting_lighting_map_shader_uniform.h"
#include "../game_data.h"
#include "../vertex_specification/color_vertex_specification.h"

void LearnOpenGlLightingMultipleLightsScene::OnStart() {
    // Preparing shaders
    vertex_color_shader_.BuildFromFile(
            "shader/vertex_color.vert",
            "shader/vertex_color.frag",
            "outColor");
    multiple_lights_shader_.BuildFromFile(
            "shader/learnopengl_lighting_multiple_lights.vert",
            "shader/learnopengl_lighting_multiple_lights.frag",
            "io_color");

    // Preparing the axis on the origin.
    axis_shader_uniform_.SetUniformLocations(
            vertex_color_shader_.GetUniformVariableLocation("projection_mat"),
            vertex_color_shader_.GetUniformVariableLocation("view_mat"),
            vertex_color_shader_.GetUniformVariableLocation("model_mat"));
    axis_.Initialize(
            GameData::kAxisVerticesSize,
            (void *) GameData::kAxisVertices,
            ColorVertexSpecification{
                    vertex_color_shader_.GetAttribVariableLocation("position"),
                    vertex_color_shader_.GetAttribVariableLocation("color")
            },
            &vertex_color_shader_,
            &axis_shader_uniform_,
            GL_STATIC_DRAW,
            GL_LINES,
            6);

    container_texture_.Load(
            "./texture/container2.png",
            Texture::ImageFormat::RGBA,
            1);
    container_specular_map_texture_.Load(
            "./texture/container2_specular.png",
            Texture::ImageFormat::RGBA,
            2);

    // Projection 行列を設定
    const glm::mat4 projection_mat = glm::perspective(glm::radians(45.0f), 8.f / 6.f, 1.f, 50.0f);
    axis_shader_uniform_.SetProjectionMat(projection_mat);
}

void LearnOpenGlLightingMultipleLightsScene::OnFrame() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // カメラの位置
    const glm::vec3 view_position = glm::vec3(0, 1.f, 6.f);

    // View 行列を設定
    const glm::mat4 view_mat = glm::lookAt(
            view_position,
            glm::vec3(0.f, 0.f, 0.f),
            glm::vec3(0.f, 1.f, 0.f));

    axis_shader_uniform_.SetViewMat(view_mat);
    axis_shader_uniform_.SetModelMat(glm::mat4(1));
    axis_.Render();
}

void LearnOpenGlLightingMultipleLightsScene::OnDestroy() {
    vertex_color_shader_.Finalize();
    multiple_lights_shader_.Finalize();

    container_texture_.Finalize();
    container_specular_map_texture_.Finalize();

    container_.Finalize();
    axis_.Finalize();
}

void LearnOpenGlLightingMultipleLightsScene::OnKey(int glfw_key, int glfw_action) {
    // ESC の場合はとりあえずアプリケーションを終了する
    if (glfw_key == GLFW_KEY_ESCAPE && glfw_action == GLFW_PRESS) {
        SendToDestroy();
    }
}
