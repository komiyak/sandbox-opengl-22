#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "learn_open_gl_lighting_multiple_lights_scene.h"
#include "../application/application.h"
#include "../game_data.h"
#include "../vertex_specification/color_vertex_specification.h"
#include "../vertex_specification/position_with_normal_and_texcoord_vertex_specification.h"

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
    axis_shader_uniform_.SetShader(&vertex_color_shader_);
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

    container_shader_uniform_.SetShader(&multiple_lights_shader_);
    container_.Initialize(
            sizeof(GameData::kCubeWithNormalAndTexcoordVertices),
            (void *) GameData::kCubeWithNormalAndTexcoordVertices,
            PositionWithNormalAndTexcoordVertexSpecification{
                    multiple_lights_shader_.GetAttribVariableLocation("vertex_position"),
                    multiple_lights_shader_.GetAttribVariableLocation("vertex_normal"),
                    multiple_lights_shader_.GetAttribVariableLocation("vertex_texcoord")
            },
            &multiple_lights_shader_,
            &container_shader_uniform_,
            GL_STATIC_DRAW,
            GL_TRIANGLES,
            36);

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
    container_shader_uniform_.SetProjectionMat(projection_mat);

    // container の設定
    container_shader_uniform_.SetMaterial(LearnopenglLightingMultipleLightsShaderUniform::Material{
            container_texture_.GetTextureUnitNumber(),
            container_specular_map_texture_.GetTextureUnitNumber(),
            32.f});
    container_shader_uniform_.SetDirectionalLight(LearnopenglLightingMultipleLightsShaderUniform::DirectionalLight{
            glm::vec3(0, -1, 0),
            glm::vec3(0.1f),
            glm::vec3(0.5f),
            glm::vec3(1.0f)});
    container_shader_uniform_.SetSpotlight(LearnopenglLightingMultipleLightsShaderUniform::Spotlight{
            glm::vec3(0, 1.f, 6.f),
            -glm::vec3(0, 1.f, 6.f),
            glm::cos(glm::pi<float>() / 128),
            glm::cos((glm::pi<float>() / 128)),
            glm::vec3(0.f),
            glm::vec3(1.f),
            glm::vec3(1.f),
            1.0f,
            0.027f,
            0.0028f});

    glm::vec3 pointLightPositions[] = {
            glm::vec3(2.f, 0.f, 2.f),
            glm::vec3(2.f, 0.f, -2.f),
            glm::vec3(-2.0f, 0.f, -2.f),
            glm::vec3(-2.0f, 0.f, 2.0f)
    };
    for (int i = 0; i < 4; i++) {
        container_shader_uniform_.SetPointLight(LearnopenglLightingMultipleLightsShaderUniform::PointLight{
                pointLightPositions[i],
                1.0f,
                0.09f,
                0.032f,
                glm::vec3(0.0f),
                glm::vec3(0.75f),
                glm::vec3(1.0f)}, i);
    }
}

void LearnOpenGlLightingMultipleLightsScene::OnFrame() {
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    angle_ += GetFrame().GetDeltaTimeF() * 3;

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

    container_shader_uniform_.SetViewPosition(view_position);
    container_shader_uniform_.SetViewMat(view_mat);

    constexpr static struct ContainerLocation {
        glm::vec3 position; // グローバル座標
        glm::vec3 rotation_speed; // 回転速度
    } container_locations[] = {
            {glm::vec3(0.0f, 0.0f, -1.5f),    glm::vec3(0.2, 0.1, 0)},
            {glm::vec3(2.0f, 5.0f, -15.0f),   glm::vec3(-0.1, 0, 0.2)},
            {glm::vec3(-1.5f, -2.2f, -2.5f),  glm::vec3(0.3, -0.1, 0)},
            {glm::vec3(-3.8f, -2.0f, -12.3f), glm::vec3(-0.5, 0.5, 0.1)},
            {glm::vec3(2.4f, -0.4f, -3.5f),   glm::vec3(0, 0.05, -0.3)},
            {glm::vec3(-1.7f, 3.0f, -7.5f),   glm::vec3(0.05, -0.35, -0.05)},
            {glm::vec3(1.3f, -2.0f, -2.5f),   glm::vec3(-0.35, 0.05, -0.1)},
            {glm::vec3(1.5f, 2.0f, -2.5f),    glm::vec3(0.05, 0.35, 0.1)},
            {glm::vec3(1.5f, 0.2f, -1.5f),    glm::vec3(-0.05, -0.15, 0.3)},
            {glm::vec3(-1.3f, 1.0f, -1.5f),   glm::vec3(0, -0.25, -0.18)},
    };
    for (const auto &container_location: container_locations) {
        glm::mat4 model_mat = glm::mat4(1);
        model_mat = glm::translate(model_mat, container_location.position);
        model_mat = glm::rotate(model_mat, container_location.rotation_speed.z * angle_, glm::vec3(0, 0, 1));
        model_mat = glm::rotate(model_mat, container_location.rotation_speed.y * angle_, glm::vec3(0, 1, 0));
        model_mat = glm::rotate(model_mat, container_location.rotation_speed.x * angle_, glm::vec3(1, 0, 0));
        container_shader_uniform_.SetModelMat(model_mat);
        container_.Render();
    }
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
