#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "lighting_example_activity.h"
#include "game_data.h"
#include "shader.h"
#include "shader_data.h"
#include "vertex_render_object.h"
#include "basic_shader_uniform.h"
#include "position_vertex_specification.h"
#include "color_vertex_specification.h"

void LightingExampleActivity::OnFrame() {
    frame_.StartFrame();

    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    angle_ += glm::pi<float>() * 0.25f * (float) frame_.GetDeltaTime();

    // View 行列を設定
    const glm::mat4 view_mat = glm::lookAt(
            glm::vec3(glm::cos(angle_) * 8.0f, 1.f, glm::sin(angle_) * 12.0f),
            glm::vec3(0.f, 0.f, 0.f),
            glm::vec3(0.f, 1.f, 0.f));

    if (up_grid_ && up_grid_shader_uniform_) {
        up_grid_shader_uniform_->SetViewMat(view_mat);
        up_grid_shader_uniform_->SetModelMat(glm::mat4(1.0f));
        up_grid_->Render();
    }
    if (up_light_source_ && up_light_source_shader_uniform_) {
        up_light_source_shader_uniform_->SetViewMat(view_mat);
        up_light_source_shader_uniform_->SetModelMat(glm::mat4(1.0f));
        up_light_source_->Render();
    }
}

void LightingExampleActivity::OnKey(int glfw_key, int glfw_action) {
    // ESC の場合はとりあえずアプリケーションを終了する
    if (glfw_key == GLFW_KEY_ESCAPE && glfw_action == GLFW_PRESS) {
        should_destroy_ = true;
    }
}

void LightingExampleActivity::OnStart() {
    up_white_vertex_shader_ = new Shader();
    up_white_vertex_shader_->BuildFromFile(
            "shader/white_vertex.vert",
            "shader/white_vertex.frag",
            shader_data::kAttribVariableLocationsOfWhiteVertexShader,
            shader_data::kAttribVariableLocationsOfWhiteVertexShaderSize,
            shader_data::kUniformVariableLocationsOfWhiteVertexShader,
            shader_data::kUniformVariableLocationsOfWhiteVertexShaderSize);

    up_vertex_color_shader_ = new Shader();
    up_vertex_color_shader_->BuildFromFile(
            "shader/vertex_color.vert",
            "shader/vertex_color.frag",
            shader_data::kAttribVariableLocationsOfVertexColorShader,
            shader_data::kAttribVariableLocationsOfVertexColorShaderSize,
            shader_data::kUniformVariableLocationsOfVertexColorShader,
            shader_data::kUniformVariableLocationsOfVertexColorShaderSize);

    up_grid_shader_uniform_ = new BasicShaderUniform{
            up_white_vertex_shader_->GetUniformVariableLocation("projection_mat"),
            up_white_vertex_shader_->GetUniformVariableLocation("view_mat"),
            up_white_vertex_shader_->GetUniformVariableLocation("model_mat")};
    up_light_source_shader_uniform_ = new BasicShaderUniform{
            up_white_vertex_shader_->GetUniformVariableLocation("projection_mat"),
            up_white_vertex_shader_->GetUniformVariableLocation("view_mat"),
            up_white_vertex_shader_->GetUniformVariableLocation("model_mat")};

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

    // Projection 行列を設定
    const glm::mat4 projection_mat = glm::perspective(glm::radians(45.0f), 8.f / 6.f, 1.f, 50.0f);
    up_grid_shader_uniform_->SetProjectionMat(projection_mat);
    up_light_source_shader_uniform_->SetProjectionMat(projection_mat);
}

void LightingExampleActivity::OnDestroy() {
    FINALIZE_AND_DELETE(up_white_vertex_shader_);
    FINALIZE_AND_DELETE(up_vertex_color_shader_);

    FINALIZE_AND_DELETE(up_grid_);
    FINALIZE_AND_DELETE(up_light_source_);

    SAFE_DELETE(up_grid_shader_uniform_);
    SAFE_DELETE(up_light_source_shader_uniform_);
}

void LightingExampleActivity::OnFrameAfterSwap() {
    frame_.EndFrame();
}
