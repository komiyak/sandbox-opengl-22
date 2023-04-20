#include <gl_app/debug.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "learn_open_gl_lighting_light_casters_scene.h"
#include "../game_data.h"
#include "../vertex_specification/position_with_normal_and_texcoord_vertex_specification.h"
#include "../vertex_specification/color_vertex_specification.h"

void LearnOpenGlLightingLightCastersScene::OnStart() {
    // Preparing shaders
    container_shader_->BuildFromFile(
            "shader/learnopengl_lighting_directional_light.vert",
            "shader/learnopengl_lighting_directional_light.frag",
            "outColor");
    container_point_light_shader_->BuildFromFile(
            "shader/learnopengl_lighting_point_light.vert",
            "shader/learnopengl_lighting_point_light.frag",
            "outColor");
    container_spotlight_shader_->BuildFromFile(
            "shader/learnopengl_lighting_spotlight.vert",
            "shader/learnopengl_lighting_spotlight.frag",
            "outColor");
    vertex_color_shader_->BuildFromFile(
            "shader/vertex_color.vert",
            "shader/vertex_color.frag",
            "outColor");
    font_shader_->BuildFromFile(
            "shader/font.vert",
            "shader/font.frag",
            "outColor");

    // Preparing containers.
    container_shader_uniform_->SetShader(container_shader_);
    container_point_light_shader_uniform_->SetShader(container_point_light_shader_);
    container_spotlight_shader_uniform_->SetShader(container_spotlight_shader_);
    container_.Create(
            sizeof(GameData::kCubeWithNormalAndTexcoordVertices),
            (void *) GameData::kCubeWithNormalAndTexcoordVertices,
            container_shader_,
            container_shader_uniform_,
            PositionWithNormalAndTexcoordVertexSpecification::UseSpecification,
            GL_STATIC_DRAW,
            GL_TRIANGLES,
            36);

    // Preparing the axis on the origin.
    axis_shader_uniform_->SetShader(vertex_color_shader_);
    axis_.Create(
            GameData::kAxisVerticesSize,
            (void *) GameData::kAxisVertices,
            vertex_color_shader_,
            axis_shader_uniform_,
            ColorVertexSpecification::UseSpecification,
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

    // フォント準備
    if (auto application_context = GetApplicationContext().lock()) {
        bitmap_font_render_.Create(
                application_context->GetWindowScreenWidth(),
                application_context->GetWindowScreenHeight(),
                font_texture_.GetTextureWidth(),
                font_texture_.GetTextureHeight(),
                4,
                8,
                font_texture_.GetTextureUnitNumber(),
                font_shader_);
    }

    // Projection 行列を設定
    const glm::mat4 projection_mat = glm::perspective(glm::radians(45.0f), 8.f / 6.f, 1.f, 50.0f);
    container_shader_uniform_->SetProjectionMat(projection_mat);
    container_point_light_shader_uniform_->SetProjectionMat(projection_mat);
    container_spotlight_shader_uniform_->SetProjectionMat(projection_mat);
    axis_shader_uniform_->SetProjectionMat(projection_mat);

    // container の設定
    container_shader_uniform_->SetMaterialDiffuse(container_texture_.GetTextureUnitNumber());
    container_shader_uniform_->SetMaterialSpecular(container_specular_map_texture_.GetTextureUnitNumber());

    // point light の設定
    container_point_light_shader_uniform_->SetMaterialDiffuse(container_texture_.GetTextureUnitNumber());
    container_point_light_shader_uniform_->SetMaterialSpecular(container_specular_map_texture_.GetTextureUnitNumber());
    container_point_light_shader_uniform_->SetLightConstant(1.0f);
    container_point_light_shader_uniform_->SetLightLinear(0.09f);
    container_point_light_shader_uniform_->SetLightQuadratic(0.032f);

    // spotlight の設定
    container_spotlight_shader_uniform_->SetMaterialDiffuse(container_texture_.GetTextureUnitNumber());
    container_spotlight_shader_uniform_->SetMaterialSpecular(container_specular_map_texture_.GetTextureUnitNumber());
    container_spotlight_shader_uniform_->SetLightCutoff(glm::cos(glm::pi<float>() / 16));
    container_spotlight_shader_uniform_->SetLightOuterCutoff(
            glm::cos((glm::pi<float>() / 16) + (glm::pi<float>() / 64)));
    container_spotlight_shader_uniform_->SetLightConstant(1.0f);
    container_spotlight_shader_uniform_->SetLightLinear(0.027f);
    container_spotlight_shader_uniform_->SetLightQuadratic(0.0028f);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"

void LearnOpenGlLightingLightCastersScene::OnFrame() {

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

    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    angle_ += GetFrame().GetDeltaTimeF() * 3;
    point_light_position_x_ += GetFrame().GetDeltaTimeF();

    // カメラの位置
    const glm::vec3 view_position = glm::vec3(0, 1.f, 6.f);

    // View 行列を設定
    const glm::mat4 view_mat = glm::lookAt(
            view_position,
            glm::vec3(0.f, 0.f, 0.f),
            glm::vec3(0.f, 1.f, 0.f));

    // directional light の向きを少し変える
    if (mode_ == kDirectionalLight) {
        switch (directional_light_mode_) {
            case kDirectionalLightA:
                container_shader_uniform_->SetLightDirection(glm::vec3(-0.1, -1, -2));
                break;
            case kDirectionalLightB:
                container_shader_uniform_->SetLightDirection(glm::vec3(-0.1, -1, 1));
                break;
            case kDirectionalLightC:
                container_shader_uniform_->SetLightDirection(glm::vec3(-0.1, 1, -0.1)); // 下からの光
                break;
            default:
                GL_APP_DEBUG_ABORT_MESSAGE("Not reached");
        }
    }

    const glm::vec3 point_light_position = glm::vec3(glm::sin(point_light_position_x_) * 2.5, 0, 0);

    // コンテナ関係の shader uniform
    container_shader_uniform_->SetViewMat(view_mat);
    container_shader_uniform_->SetLightAmbient(glm::vec3(0.25f));
    container_shader_uniform_->SetLightDiffuse(glm::vec3(0.8f));
    container_shader_uniform_->SetLightSpecular(glm::vec3(1.0f));
    container_shader_uniform_->SetViewPosition(view_position);
    container_shader_uniform_->SetMaterialShininess(32.0f);
    container_point_light_shader_uniform_->SetViewMat(view_mat);
    container_point_light_shader_uniform_->SetLightAmbient(glm::vec3(0.25f));
    container_point_light_shader_uniform_->SetLightDiffuse(glm::vec3(0.8f));
    container_point_light_shader_uniform_->SetLightSpecular(glm::vec3(1.0f));
    container_point_light_shader_uniform_->SetViewPosition(view_position);
    container_point_light_shader_uniform_->SetMaterialShininess(32.0f);
    container_point_light_shader_uniform_->SetLightPosition(point_light_position);
    container_spotlight_shader_uniform_->SetViewMat(view_mat);
    container_spotlight_shader_uniform_->SetLightAmbient(glm::vec3(0.25f));
    container_spotlight_shader_uniform_->SetLightDiffuse(glm::vec3(0.8f));
    container_spotlight_shader_uniform_->SetLightSpecular(glm::vec3(1.0f));
    container_spotlight_shader_uniform_->SetViewPosition(view_position);
    container_spotlight_shader_uniform_->SetMaterialShininess(32.0f);
    container_spotlight_shader_uniform_->SetLightPosition(view_position);
    container_spotlight_shader_uniform_->SetLightDirection(glm::normalize(-view_position));
    for (const auto &container_location: container_locations) {
        glm::mat4 model_mat = glm::mat4(1);
        model_mat = glm::translate(model_mat, container_location.position);
        model_mat = glm::rotate(model_mat, container_location.rotation_speed.z * angle_, glm::vec3(0, 0, 1));
        model_mat = glm::rotate(model_mat, container_location.rotation_speed.y * angle_, glm::vec3(0, 1, 0));
        model_mat = glm::rotate(model_mat, container_location.rotation_speed.x * angle_, glm::vec3(1, 0, 0));
        container_shader_uniform_->SetModelMat(model_mat);
        container_point_light_shader_uniform_->SetModelMat(model_mat);
        container_spotlight_shader_uniform_->SetModelMat(model_mat);
        container_.Render();
    }

    axis_shader_uniform_->SetViewMat(view_mat);
    axis_shader_uniform_->SetModelMat(glm::mat4(1));
    axis_.Render();

    if (mode_ == kPointLight) {
        // point light
        glm::mat4 point_light_model_mat = glm::mat4(1);
        point_light_model_mat = glm::translate(point_light_model_mat, point_light_position);
        axis_shader_uniform_->SetModelMat(point_light_model_mat);
        axis_.Render();
    }

    // フォント描画
    if (true) {
        const char *current_mode;
        const char *current_sub_mode = nullptr;
        switch (mode_) {
            case kDirectionalLight:
                current_mode = "Current mode is: Directional light";
                switch (directional_light_mode_) {
                    case kDirectionalLightA:
                        current_sub_mode = "Directional light mode is: A";
                        break;
                    case kDirectionalLightB:
                        current_sub_mode = "Directional light mode is: B";
                        break;
                    case kDirectionalLightC:
                        current_sub_mode = "Directional light mode is: C";
                        break;
                    default:
                        GL_APP_DEBUG_ABORT_MESSAGE("Not reached");
                }
                break;
            case kPointLight:
                current_mode = "Current mode is: Point light";
                break;
            case kSpotlight:
                current_mode = "Current mode is: Spotlight";
                break;
            default:
                GL_APP_DEBUG_ABORT_MESSAGE("Not reached");
        }
        bitmap_font_render_.RenderWhiteAsciiText(current_mode, 40, 40, 20);
        bitmap_font_render_.RenderAsciiText(
                "To change the mode, [1]: Directional light, [2]: Point light, [3]: Spotlight",
                40, 90, 14,
                glm::vec3(0, 0.7, 0));

        if (current_sub_mode) {
            bitmap_font_render_.RenderWhiteAsciiText(current_sub_mode, 40, 150, 20);
            bitmap_font_render_.RenderAsciiText(
                    "To change the sub mode, [A]: A, [S]: B, [D]: C",
                    40, 200, 14,
                    glm::vec3(0, 0.7, 0));
        }
    }
}

#pragma clang diagnostic pop

void LearnOpenGlLightingLightCastersScene::OnDestroy() {
}

void LearnOpenGlLightingLightCastersScene::OnKey(int glfw_key, int glfw_action) {
    // ESC の場合はとりあえずアプリケーションを終了する
    if (glfw_key == GLFW_KEY_ESCAPE && glfw_action == GLFW_PRESS) {
        SendToDestroy();
    }

    // mode change
    if (glfw_key == GLFW_KEY_1 && glfw_action == GLFW_PRESS) {
        if (mode_ != kDirectionalLight) {
            container_.ChangeShader(
                    container_shader_,
                    container_shader_uniform_);
        }
        mode_ = kDirectionalLight;
    }
    if (glfw_key == GLFW_KEY_2 && glfw_action == GLFW_PRESS) {
        if (mode_ != kPointLight) {
            container_.ChangeShader(
                    container_point_light_shader_,
                    container_point_light_shader_uniform_);
        }
        mode_ = kPointLight;
    }
    if (glfw_key == GLFW_KEY_3 && glfw_action == GLFW_PRESS) {
        if (mode_ != kSpotlight) {
            container_.ChangeShader(
                    container_spotlight_shader_,
                    container_spotlight_shader_uniform_);
        }
        mode_ = kSpotlight;
    }

    if (mode_ == kDirectionalLight) {
        if (glfw_key == GLFW_KEY_A && glfw_action == GLFW_PRESS) {
            directional_light_mode_ = kDirectionalLightA;
        }
        if (glfw_key == GLFW_KEY_S && glfw_action == GLFW_PRESS) {
            directional_light_mode_ = kDirectionalLightB;
        }
        if (glfw_key == GLFW_KEY_D && glfw_action == GLFW_PRESS) {
            directional_light_mode_ = kDirectionalLightC;
        }
    }
}
