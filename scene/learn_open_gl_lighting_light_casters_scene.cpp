#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "learn_open_gl_lighting_light_casters_scene.h"
#include "../game_data.h"
#include "../position_with_normal_and_texcoord_vertex_specification.h"
#include "../color_vertex_specification.h"

void LearnOpenGlLightingLightCastersScene::OnStart() {
    // Preparing shaders
    container_shader_.BuildFromFile(
            "shader/learnopengl_lighting_directional_light.vert",
            "shader/learnopengl_lighting_directional_light.frag");
    vertex_color_shader_.BuildFromFile(
            "shader/vertex_color.vert",
            "shader/vertex_color.frag");

    // Preparing containers.
    container_shader_uniform_.SetUniformLocations(
            container_shader_.GetUniformVariableLocation("projection_mat"),
            container_shader_.GetUniformVariableLocation("view_mat"),
            container_shader_.GetUniformVariableLocation("model_mat"),
            container_shader_.GetUniformVariableLocation("light.ambient"),
            container_shader_.GetUniformVariableLocation("light.diffuse"),
            container_shader_.GetUniformVariableLocation("light.specular"),
            container_shader_.GetUniformVariableLocation("material.diffuse"),
            container_shader_.GetUniformVariableLocation("material.specular"),
            container_shader_.GetUniformVariableLocation("material.shininess"),
            container_shader_.GetUniformVariableLocation("viewPosition"));
    container_.Initialize(
            sizeof(GameData::kCubeWithNormalAndTexcoordVertices),
            (void *) GameData::kCubeWithNormalAndTexcoordVertices,
            PositionWithNormalAndTexcoordVertexSpecification{
                    container_shader_.GetAttribVariableLocation("position"),
                    container_shader_.GetAttribVariableLocation("normal"),
                    container_shader_.GetAttribVariableLocation("texcoord")
            },
            &container_shader_,
            &container_shader_uniform_,
            GL_STATIC_DRAW,
            GL_TRIANGLES,
            36);

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

    font_texture_.Load(
            "./texture/ascii_bitmap_font.png",
            Texture::ImageFormat::RGBA,
            0);
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
    container_shader_uniform_.SetProjectionMat(projection_mat);
    axis_shader_uniform_.SetProjectionMat(projection_mat);

    // container の設定
    container_shader_uniform_.SetMaterialDiffuse(container_texture_.GetTextureUnitNumber());
    container_shader_uniform_.SetMaterialSpecular(container_specular_map_texture_.GetTextureUnitNumber());
}

void LearnOpenGlLightingLightCastersScene::OnFrame() {

    constexpr static struct ContainerLocation {
        glm::vec3 position; // グローバル座標
        glm::vec3 rotation_speed; // 回転速度
    } container_locations[] = {
            {glm::vec3(0.0f, 0.0f, -0.5f),    glm::vec3(0.2, 0.1, 0)},
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

    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    angle_ += GetFrame().GetDeltaTimeF() * 3;

    // カメラの位置
    const glm::vec3 view_position = glm::vec3(0, 1.f, 6.f);

    // View 行列を設定
    const glm::mat4 view_mat = glm::lookAt(
            view_position,
            glm::vec3(0.f, 0.f, 0.f),
            glm::vec3(0.f, 1.f, 0.f));


    container_shader_uniform_.SetViewMat(view_mat);
    container_shader_uniform_.SetLightAmbient(glm::vec3(0.25f));
    container_shader_uniform_.SetLightDiffuse(glm::vec3(0.8f));
    container_shader_uniform_.SetLightSpecular(glm::vec3(1.0f));
    container_shader_uniform_.SetViewPosition(view_position);
    container_shader_uniform_.SetMaterialShininess(32.0f);
    for (const auto &container_location: container_locations) {
        glm::mat4 model_mat = glm::mat4(1);
        model_mat = glm::translate(model_mat, container_location.position);
        model_mat = glm::rotate(model_mat, container_location.rotation_speed.z * angle_, glm::vec3(0, 0, 1));
        model_mat = glm::rotate(model_mat, container_location.rotation_speed.y * angle_, glm::vec3(0, 1, 0));
        model_mat = glm::rotate(model_mat, container_location.rotation_speed.x * angle_, glm::vec3(1, 0, 0));
        container_shader_uniform_.SetModelMat(model_mat);
        container_.Render();
    }

    axis_shader_uniform_.SetViewMat(view_mat);
    axis_shader_uniform_.SetModelMat(glm::mat4(1));
    axis_.Render();
}

void LearnOpenGlLightingLightCastersScene::OnDestroy() {
    container_shader_.Finalize();
    vertex_color_shader_.Finalize();

    font_texture_.Finalize();
    container_texture_.Finalize();
    container_specular_map_texture_.Finalize();

    container_.Finalize();
    axis_.Finalize();
}

void LearnOpenGlLightingLightCastersScene::OnKey(int glfw_key, int glfw_action) {
    // ESC の場合はとりあえずアプリケーションを終了する
    if (glfw_key == GLFW_KEY_ESCAPE && glfw_action == GLFW_PRESS) {
        should_destroy_ = true;
    }
}
