#include <gl_app/debug_util.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "learn_open_gl_lighting_scene.h"
#include "../game_data.h"
#include "../vertex_specification/position_vertex_specification.h"
#include "../vertex_specification/position_with_normal_vector_vertex_specification.h"
#include "../vertex_specification/position_with_normal_and_texcoord_vertex_specification.h"
#include "../vertex_specification/color_vertex_specification.h"

void LearnOpenGlLightingScene::OnFrame() {
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    angle_ += glm::pi<float>() * 0.1f * (float) GetFrame().GetDeltaTime();
    light_angle_ += glm::pi<float>() * 0.1f * (float) GetFrame().GetDeltaTime();
    light_strength_ = 1;

    // 光源の位置
    const glm::vec3 light_position = glm::vec3(
            glm::sin(light_angle_) * 2,
            glm::sin(light_angle_) * 4.f,
            glm::cos(light_angle_) * 2.0f);
    // カメラの位置
    const glm::vec3 view_position = glm::vec3(glm::cos(angle_) * 4.0f, 2.f, glm::sin(angle_) * 6.0f);

    // View 行列を設定
    const glm::mat4 view_mat = glm::lookAt(
            view_position,
            glm::vec3(0.f, 0.f, 0.f),
            glm::vec3(0.f, 1.f, 0.f));

    if (grid_shader_uniform_) {
        grid_shader_uniform_->SetViewMat(view_mat);
        grid_shader_uniform_->SetModelMat(glm::mat4(1.0f));
        grid_.Render();
    }

    if (light_source_shader_uniform_) {
        glm::mat4 model_mat = glm::mat4(1);
        model_mat = glm::translate(model_mat, light_position);

        light_source_shader_uniform_->SetViewMat(view_mat);
        light_source_shader_uniform_->SetModelMat(model_mat);
        light_source_.Render();
    }

    if (lighting_target_shader_uniform_) {
        glm::mat4 model_mat = glm::mat4(1);
        model_mat = glm::translate(model_mat, glm::vec3(-3, 0.5, 3));

        float light_strength = glm::sin(light_strength_) * 0.5f + 0.5f;

        lighting_target_shader_uniform_->SetViewMat(view_mat);
        lighting_target_shader_uniform_->SetModelMat(model_mat);
        lighting_target_shader_uniform_->SetLightAmbient(glm::vec3(0.25f * light_strength));
        lighting_target_shader_uniform_->SetLightDiffuse(glm::vec3(0.8f * light_strength));
        lighting_target_shader_uniform_->SetLightSpecular(glm::vec3(1.0f * light_strength));
        lighting_target_shader_uniform_->SetLightPosition(light_position);
        lighting_target_shader_uniform_->SetViewPosition(view_position);
        lighting_target_shader_uniform_->SetMaterialAmbient(glm::vec3(1.0, 0.5, 0.31));
        lighting_target_shader_uniform_->SetMaterialDiffuse(glm::vec3(1.0, 0.5, 0.31));
        lighting_target_shader_uniform_->SetMaterialSpecular(glm::vec3(0.5, 0.5, 0.5));
        lighting_target_shader_uniform_->SetMaterialShininess(32.0f);
        lighting_target_.Render();


        // 位置を変えて描画
        model_mat = glm::translate(glm::mat4(1), glm::vec3(3, 0.5, 3));
        lighting_target_shader_uniform_->SetModelMat(model_mat);
        lighting_target_shader_uniform_->SetMaterialAmbient(glm::vec3(0.212f, 0.127, 0.054));
        lighting_target_shader_uniform_->SetMaterialDiffuse(glm::vec3(0.714f, 0.428f, 0.182f));
        lighting_target_shader_uniform_->SetMaterialSpecular(glm::vec3(0.393f, 0.271f, 0.166f));
        lighting_target_shader_uniform_->SetMaterialShininess(32.0f);
        lighting_target_.Render();

        model_mat = glm::translate(glm::mat4(1), glm::vec3(-4, 0.5, -4));
        lighting_target_shader_uniform_->SetModelMat(model_mat);
        lighting_target_shader_uniform_->SetMaterialAmbient(glm::vec3(0.0, 0.05, 0.0));
        lighting_target_shader_uniform_->SetMaterialDiffuse(glm::vec3(0.4, 0.5, 0.4));
        lighting_target_shader_uniform_->SetMaterialSpecular(glm::vec3(0.04, 0.7, 0.04));
        lighting_target_shader_uniform_->SetMaterialShininess(256.0f);
        lighting_target_.Render();

        model_mat = glm::translate(glm::mat4(1), glm::vec3(4, 0.5, -7));
        lighting_target_shader_uniform_->SetModelMat(model_mat);
        lighting_target_shader_uniform_->SetMaterialAmbient(glm::vec3(0.0, 0.0, 0.0));
        lighting_target_shader_uniform_->SetMaterialDiffuse(glm::vec3(0.5, 0.0, 0.0));
        lighting_target_shader_uniform_->SetMaterialSpecular(glm::vec3(0.7, 0.6, 0.6));
        lighting_target_shader_uniform_->SetMaterialShininess(16.0f);
        lighting_target_.Render();
    }

    if (lighting_map_shader_uniform_) {
        glm::mat4 model_mat = glm::mat4(1);
        model_mat = glm::translate(model_mat, glm::vec3(0, 0.5, 0));

        lighting_map_shader_uniform_->SetViewMat(view_mat);
        lighting_map_shader_uniform_->SetModelMat(model_mat);
        lighting_map_shader_uniform_->SetLightAmbient(glm::vec3(0.25f));
        lighting_map_shader_uniform_->SetLightDiffuse(glm::vec3(0.8f));
        lighting_map_shader_uniform_->SetLightSpecular(glm::vec3(1.0f));
        lighting_map_shader_uniform_->SetLightPosition(light_position);
        lighting_map_shader_uniform_->SetViewPosition(view_position);
        lighting_map_shader_uniform_->SetMaterialDiffuse(texture_diffuse_map_.GetTextureUnitNumber());
        lighting_map_shader_uniform_->SetMaterialSpecular(texture_specular_map_.GetTextureUnitNumber());
        lighting_map_shader_uniform_->SetMaterialShininess(32.0f);
        lighting_map_shader_uniform_->SetEmission(texture_emission_map_.GetTextureUnitNumber());
        lighting_map_cube_.Render();
    }
}

void LearnOpenGlLightingScene::OnKey(int glfw_key, int glfw_action) {
    // ESC の場合はとりあえずアプリケーションを終了する
    if (glfw_key == GLFW_KEY_ESCAPE && glfw_action == GLFW_PRESS) {
        SendToDestroy();
    }
}

void LearnOpenGlLightingScene::OnStart() {
    white_vertex_shader_->BuildFromFile(
            "shader/white_vertex.vert",
            "shader/white_vertex.frag",
            "outColor");

    vertex_color_shader_->BuildFromFile(
            "shader/vertex_color.vert",
            "shader/vertex_color.frag",
            "outColor");

    sample_lighting_cube_shader_->BuildFromFile(
            "shader/practice_lighting_phong_shading.vert",
            "shader/practice_lighting_phong_shading.frag",
            "outColor");

    lighting_map_shader_->BuildFromFile(
            "shader/practice_lighting_lighting_map.vert",
            "shader/practice_lighting_lighting_map.frag",
            "outColor");

    grid_shader_uniform_->SetShader(vertex_color_shader_);
    light_source_shader_uniform_->SetShader(white_vertex_shader_);
    lighting_target_shader_uniform_->SetShader(sample_lighting_cube_shader_);
    lighting_map_shader_uniform_->SetShader(lighting_map_shader_);

    grid_.Create(
            sizeof(GameData::kGridVertices),
            (void *) GameData::kGridVertices,
            white_vertex_shader_,
            grid_shader_uniform_,
            PositionVertexSpecification::UseSpecification,
            GL_STATIC_DRAW,
            GL_LINES,
            22 * 2);
    light_source_.Create(
            GameData::kAxisVerticesSize,
            (void *) GameData::kAxisVertices,
            vertex_color_shader_,
            light_source_shader_uniform_,
            ColorVertexSpecification::UseSpecification,
            GL_STATIC_DRAW,
            GL_LINES,
            6);
    lighting_target_.Create(
            sizeof(GameData::kCubeWithNormalVertices),
            (void *) GameData::kCubeWithNormalVertices,
            sample_lighting_cube_shader_,
            lighting_target_shader_uniform_,
            PositionWithNormalVectorVertexSpecification::UseSpecification,
            GL_STATIC_DRAW,
            GL_TRIANGLES,
            36);
    lighting_map_cube_.Create(
            sizeof(GameData::kCubeWithNormalAndTexcoordVertices),
            (void *) GameData::kCubeWithNormalAndTexcoordVertices,
            lighting_map_shader_,
            lighting_map_shader_uniform_,
            PositionWithNormalAndTexcoordVertexSpecification::UseSpecification,
            GL_STATIC_DRAW,
            GL_TRIANGLES,
            36);

    // Projection 行列を設定
    const glm::mat4 projection_mat = glm::perspective(glm::radians(45.0f), 8.f / 6.f, 1.f, 50.0f);
    grid_shader_uniform_->SetProjectionMat(projection_mat);
    light_source_shader_uniform_->SetProjectionMat(projection_mat);
    lighting_target_shader_uniform_->SetProjectionMat(projection_mat);
    lighting_map_shader_uniform_->SetProjectionMat(projection_mat);


    texture_diffuse_map_.Load(
            "./texture/container2.png",
            Texture::ImageFormat::RGBA,
            0);
    texture_specular_map_.Load(
            "./texture/container2_specular.png",
            Texture::ImageFormat::RGBA,
            1);
    texture_emission_map_.Load(
            "./texture/container2_emission.png",
            Texture::ImageFormat::RGBA,
            2);
}

void LearnOpenGlLightingScene::OnDestroy() {
}
