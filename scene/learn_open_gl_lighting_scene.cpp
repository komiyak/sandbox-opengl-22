#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "learn_open_gl_lighting_scene.h"
#include "../application/application.h"
#include "../opengl_debug.h"
#include "../game_data.h"
#include "../shader.h"
#include "../vertex_render_object.h"
#include "../shader_uniform/basic_shader_uniform.h"
#include "../shader_uniform/practice_lighting_phong_shading_shader_uniform.h"
#include "../shader_uniform/practice_lighting_lighting_map_shader_uniform.h"
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

    if (up_grid_ && up_grid_shader_uniform_) {
        up_grid_shader_uniform_->SetViewMat(view_mat);
        up_grid_shader_uniform_->SetModelMat(glm::mat4(1.0f));
        up_grid_->Render();
    }
    if (up_light_source_ && up_light_source_shader_uniform_) {
        glm::mat4 model_mat = glm::mat4(1);
        model_mat = glm::translate(model_mat, light_position);

        up_light_source_shader_uniform_->SetViewMat(view_mat);
        up_light_source_shader_uniform_->SetModelMat(model_mat);
        up_light_source_->Render();
    }
    if (up_lighting_target_ && up_lighting_target_shader_uniform_) {
        glm::mat4 model_mat = glm::mat4(1);
        model_mat = glm::translate(model_mat, glm::vec3(-3, 0.5, 3));

        float light_strength = glm::sin(light_strength_) * 0.5f + 0.5f;

        up_lighting_target_shader_uniform_->SetViewMat(view_mat);
        up_lighting_target_shader_uniform_->SetModelMat(model_mat);
        up_lighting_target_shader_uniform_->SetLightAmbient(glm::vec3(0.25f * light_strength));
        up_lighting_target_shader_uniform_->SetLightDiffuse(glm::vec3(0.8f * light_strength));
        up_lighting_target_shader_uniform_->SetLightSpecular(glm::vec3(1.0f * light_strength));
        up_lighting_target_shader_uniform_->SetLightPosition(light_position);
        up_lighting_target_shader_uniform_->SetViewPosition(view_position);
        up_lighting_target_shader_uniform_->SetMaterialAmbient(glm::vec3(1.0, 0.5, 0.31));
        up_lighting_target_shader_uniform_->SetMaterialDiffuse(glm::vec3(1.0, 0.5, 0.31));
        up_lighting_target_shader_uniform_->SetMaterialSpecular(glm::vec3(0.5, 0.5, 0.5));
        up_lighting_target_shader_uniform_->SetMaterialShininess(32.0f);
        up_lighting_target_->Render();


        // 位置を変えて描画
        model_mat = glm::translate(glm::mat4(1), glm::vec3(3, 0.5, 3));
        up_lighting_target_shader_uniform_->SetModelMat(model_mat);
        up_lighting_target_shader_uniform_->SetMaterialAmbient(glm::vec3(0.212f, 0.127, 0.054));
        up_lighting_target_shader_uniform_->SetMaterialDiffuse(glm::vec3(0.714f, 0.428f, 0.182f));
        up_lighting_target_shader_uniform_->SetMaterialSpecular(glm::vec3(0.393f, 0.271f, 0.166f));
        up_lighting_target_shader_uniform_->SetMaterialShininess(32.0f);
        up_lighting_target_->Render();

        model_mat = glm::translate(glm::mat4(1), glm::vec3(-4, 0.5, -4));
        up_lighting_target_shader_uniform_->SetModelMat(model_mat);
        up_lighting_target_shader_uniform_->SetMaterialAmbient(glm::vec3(0.0, 0.05, 0.0));
        up_lighting_target_shader_uniform_->SetMaterialDiffuse(glm::vec3(0.4, 0.5, 0.4));
        up_lighting_target_shader_uniform_->SetMaterialSpecular(glm::vec3(0.04, 0.7, 0.04));
        up_lighting_target_shader_uniform_->SetMaterialShininess(256.0f);
        up_lighting_target_->Render();

        model_mat = glm::translate(glm::mat4(1), glm::vec3(4, 0.5, -7));
        up_lighting_target_shader_uniform_->SetModelMat(model_mat);
        up_lighting_target_shader_uniform_->SetMaterialAmbient(glm::vec3(0.0, 0.0, 0.0));
        up_lighting_target_shader_uniform_->SetMaterialDiffuse(glm::vec3(0.5, 0.0, 0.0));
        up_lighting_target_shader_uniform_->SetMaterialSpecular(glm::vec3(0.7, 0.6, 0.6));
        up_lighting_target_shader_uniform_->SetMaterialShininess(16.0f);
        up_lighting_target_->Render();
    }

    if (up_lighting_map_cube_ && up_lighting_map_shader_uniform_) {
        glm::mat4 model_mat = glm::mat4(1);
        model_mat = glm::translate(model_mat, glm::vec3(0, 0.5, 0));

        up_lighting_map_shader_uniform_->SetViewMat(view_mat);
        up_lighting_map_shader_uniform_->SetModelMat(model_mat);
        up_lighting_map_shader_uniform_->SetLightAmbient(glm::vec3(0.25f));
        up_lighting_map_shader_uniform_->SetLightDiffuse(glm::vec3(0.8f));
        up_lighting_map_shader_uniform_->SetLightSpecular(glm::vec3(1.0f));
        up_lighting_map_shader_uniform_->SetLightPosition(light_position);
        up_lighting_map_shader_uniform_->SetViewPosition(view_position);
        up_lighting_map_shader_uniform_->SetMaterialDiffuse(texture_diffuse_map_.GetTextureUnitNumber());
        up_lighting_map_shader_uniform_->SetMaterialSpecular(texture_specular_map_.GetTextureUnitNumber());
        up_lighting_map_shader_uniform_->SetMaterialShininess(32.0f);
        up_lighting_map_shader_uniform_->SetEmission(texture_emission_map_.GetTextureUnitNumber());
        up_lighting_map_cube_->Render();
    }
}

void LearnOpenGlLightingScene::OnKey(int glfw_key, int glfw_action) {
    // ESC の場合はとりあえずアプリケーションを終了する
    if (glfw_key == GLFW_KEY_ESCAPE && glfw_action == GLFW_PRESS) {
        SendToDestroy();
    }
}

void LearnOpenGlLightingScene::OnStart() {
    up_white_vertex_shader_ = new Shader();
    up_white_vertex_shader_->BuildFromFile(
            "shader/white_vertex.vert",
            "shader/white_vertex.frag",
            "outColor");

    up_vertex_color_shader_ = new Shader();
    up_vertex_color_shader_->BuildFromFile(
            "shader/vertex_color.vert",
            "shader/vertex_color.frag",
            "outColor");

    up_sample_lighting_cube_shader_ = new Shader();
    up_sample_lighting_cube_shader_->BuildFromFile(
            "shader/practice_lighting_phong_shading.vert",
            "shader/practice_lighting_phong_shading.frag",
            "outColor");

    up_lighting_map_shader_ = new Shader();
    up_lighting_map_shader_->BuildFromFile(
            "shader/practice_lighting_lighting_map.vert",
            "shader/practice_lighting_lighting_map.frag",
            "outColor");

    up_grid_shader_uniform_ = new BasicShaderUniform();
    up_grid_shader_uniform_->SetUniformLocations(
            up_vertex_color_shader_->GetUniformVariableLocation("projection_mat"),
            up_vertex_color_shader_->GetUniformVariableLocation("view_mat"),
            up_vertex_color_shader_->GetUniformVariableLocation("model_mat"));
    up_light_source_shader_uniform_ = new BasicShaderUniform();
    up_light_source_shader_uniform_->SetUniformLocations(
            up_white_vertex_shader_->GetUniformVariableLocation("projection_mat"),
            up_white_vertex_shader_->GetUniformVariableLocation("view_mat"),
            up_white_vertex_shader_->GetUniformVariableLocation("model_mat"));
    up_lighting_target_shader_uniform_ = new PracticeLightingPhongShadingShaderUniform{
            up_sample_lighting_cube_shader_->GetUniformVariableLocation("projection_mat"),
            up_sample_lighting_cube_shader_->GetUniformVariableLocation("view_mat"),
            up_sample_lighting_cube_shader_->GetUniformVariableLocation("model_mat"),
            up_sample_lighting_cube_shader_->GetUniformVariableLocation("light.position"),
            up_sample_lighting_cube_shader_->GetUniformVariableLocation("light.ambient"),
            up_sample_lighting_cube_shader_->GetUniformVariableLocation("light.diffuse"),
            up_sample_lighting_cube_shader_->GetUniformVariableLocation("light.specular"),
            up_sample_lighting_cube_shader_->GetUniformVariableLocation("viewPosition"),
            up_sample_lighting_cube_shader_->GetUniformVariableLocation("material.ambient"),
            up_sample_lighting_cube_shader_->GetUniformVariableLocation("material.diffuse"),
            up_sample_lighting_cube_shader_->GetUniformVariableLocation("material.specular"),
            up_sample_lighting_cube_shader_->GetUniformVariableLocation("material.shininess")};
    up_lighting_map_shader_uniform_ = new PracticeLightingLightingMapShaderUniform{
            up_lighting_map_shader_->GetUniformVariableLocation("projection_mat"),
            up_lighting_map_shader_->GetUniformVariableLocation("view_mat"),
            up_lighting_map_shader_->GetUniformVariableLocation("model_mat"),
            up_lighting_map_shader_->GetUniformVariableLocation("light.position"),
            up_lighting_map_shader_->GetUniformVariableLocation("light.ambient"),
            up_lighting_map_shader_->GetUniformVariableLocation("light.diffuse"),
            up_lighting_map_shader_->GetUniformVariableLocation("light.specular"),
            up_lighting_map_shader_->GetUniformVariableLocation("material.diffuse"),
            up_lighting_map_shader_->GetUniformVariableLocation("material.specular"),
            up_lighting_map_shader_->GetUniformVariableLocation("material.shininess"),
            up_lighting_map_shader_->GetUniformVariableLocation("material.emission"),
            up_lighting_map_shader_->GetUniformVariableLocation("viewPosition")};

    up_grid_ = new VertexRenderObject();
    up_grid_->Initialize(
            sizeof(GameData::kGridVertices),
            (void *) GameData::kGridVertices,
            PositionVertexSpecification{
                    up_white_vertex_shader_->GetAttribVariableLocation("position")
            },
            up_white_vertex_shader_,
            up_grid_shader_uniform_,
            GL_STATIC_DRAW,
            GL_LINES,
            22 * 2);
    up_light_source_ = new VertexRenderObject();
    up_light_source_->Initialize(
            GameData::kAxisVerticesSize,
            (void *) GameData::kAxisVertices,
            ColorVertexSpecification{
                    up_vertex_color_shader_->GetAttribVariableLocation("position"),
                    up_vertex_color_shader_->GetAttribVariableLocation("color")
            },
            up_vertex_color_shader_,
            up_light_source_shader_uniform_,
            GL_STATIC_DRAW,
            GL_LINES,
            6);

    up_lighting_target_ = new VertexRenderObject();
    up_lighting_target_->Initialize(
            sizeof(GameData::kCubeWithNormalVertices),
            (void *) GameData::kCubeWithNormalVertices,
            PositionWithNormalVectorVertexSpecification{
                    up_sample_lighting_cube_shader_->GetAttribVariableLocation("position"),
                    up_sample_lighting_cube_shader_->GetAttribVariableLocation("normal")
            },
            up_sample_lighting_cube_shader_,
            up_lighting_target_shader_uniform_,
            GL_STATIC_DRAW,
            GL_TRIANGLES,
            36);

    up_lighting_map_cube_ = new VertexRenderObject();
    up_lighting_map_cube_->Initialize(
            sizeof(GameData::kCubeWithNormalAndTexcoordVertices),
            (void *) GameData::kCubeWithNormalAndTexcoordVertices,
            PositionWithNormalAndTexcoordVertexSpecification{
                    up_lighting_map_shader_->GetAttribVariableLocation("position"),
                    up_lighting_map_shader_->GetAttribVariableLocation("normal"),
                    up_lighting_map_shader_->GetAttribVariableLocation("texcoord")
            },
            up_lighting_map_shader_,
            up_lighting_map_shader_uniform_,
            GL_STATIC_DRAW,
            GL_TRIANGLES,
            36);

    // Projection 行列を設定
    const glm::mat4 projection_mat = glm::perspective(glm::radians(45.0f), 8.f / 6.f, 1.f, 50.0f);
    up_grid_shader_uniform_->SetProjectionMat(projection_mat);
    up_light_source_shader_uniform_->SetProjectionMat(projection_mat);
    up_lighting_target_shader_uniform_->SetProjectionMat(projection_mat);
    up_lighting_map_shader_uniform_->SetProjectionMat(projection_mat);


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
    texture_diffuse_map_.Finalize();
    texture_specular_map_.Finalize();
    texture_emission_map_.Finalize();

    FINALIZE_AND_DELETE(up_white_vertex_shader_);
    FINALIZE_AND_DELETE(up_vertex_color_shader_);
    FINALIZE_AND_DELETE(up_sample_lighting_cube_shader_);
    FINALIZE_AND_DELETE(up_lighting_map_shader_);

    FINALIZE_AND_DELETE(up_grid_);
    FINALIZE_AND_DELETE(up_light_source_);
    FINALIZE_AND_DELETE(up_lighting_target_);
    FINALIZE_AND_DELETE(up_lighting_map_cube_);

    SAFE_DELETE(up_grid_shader_uniform_);
    SAFE_DELETE(up_light_source_shader_uniform_);
    SAFE_DELETE(up_lighting_target_shader_uniform_);
    SAFE_DELETE(up_lighting_map_shader_uniform_);
}
