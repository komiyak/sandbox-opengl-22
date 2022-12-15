#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "sandbox_scene.h"
#include "../application/application.h"
#include "../opengl_debug.h"
#include "../vertex_render_object.h"
#include "../shader.h"
#include "../position_vertex_specification.h"
#include "../color_vertex_specification.h"
#include "../texture_vertex_specification.h"
#include "../basic_shader_uniform.h"
#include "../texture_shader_uniform.h"
#include "../bitmap_font_render.h"
#include "../game_data.h"

void SandboxScene::OnStart() {
    // 頂点
    const GLfloat kVertices[] = {
            // x, y, z, r, g, b
            0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    };


    const GLfloat kGrassVertices[] = {
            // x, y, z, s, t
            -0.5f, -0.5f, 0.f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.f, 1.0f, 0.0f,
    };

    up_grid_shader_ = new Shader();
    up_grid_shader_->BuildFromFile(
            "shader/white_vertex.vert",
            "shader/white_vertex.frag");

    up_shader_ = new Shader();
    up_shader_->BuildFromFile(
            "shader/vertex_color.vert",
            "shader/vertex_color.frag");

    up_texture_shader_ = new Shader();
    up_texture_shader_->BuildFromFile(
            "shader/texture.vert",
            "shader/texture.frag");

    up_texture_2d_shader_ = new Shader();
    up_texture_2d_shader_->BuildFromFile(
            "shader/texture_2d.vert",
            "shader/texture_2d.frag");


    texture_grass_.Load(
            "./texture/grass.png",
            Texture::ImageFormat::RGBA,
            0);

    texture_bitmap_font_.Load(
            "./texture/ascii_bitmap_font.png",
            Texture::ImageFormat::RGBA,
            1);


    up_grid_shader_uniform_ = new BasicShaderUniform{
            up_grid_shader_->GetUniformVariableLocation("projection_mat"),
            up_grid_shader_->GetUniformVariableLocation("view_mat"),
            up_grid_shader_->GetUniformVariableLocation("model_mat")};

    up_axis_shader_uniform_ = new BasicShaderUniform{
            up_shader_->GetUniformVariableLocation("projection_mat"),
            up_shader_->GetUniformVariableLocation("view_mat"),
            up_shader_->GetUniformVariableLocation("model_mat")};

    up_triangle_shader_uniform_ = new BasicShaderUniform{
            up_shader_->GetUniformVariableLocation("projection_mat"),
            up_shader_->GetUniformVariableLocation("view_mat"),
            up_shader_->GetUniformVariableLocation("model_mat")};

    up_grass_shader_uniform_ = new TextureShaderUniform{
            up_texture_shader_->GetUniformVariableLocation("projection_mat"),
            up_texture_shader_->GetUniformVariableLocation("view_mat"),
            up_texture_shader_->GetUniformVariableLocation("model_mat"),
            up_texture_shader_->GetUniformVariableLocation("tex")};

    up_cube_shader_uniform_ = new BasicShaderUniform(
            up_grid_shader_->GetUniformVariableLocation("projection_mat"),
            up_grid_shader_->GetUniformVariableLocation("view_mat"),
            up_grid_shader_->GetUniformVariableLocation("model_mat"));

    // texture unit 0 を利用する
    up_grass_shader_uniform_->SetTextureUnit(0);

    up_grid_ = new VertexRenderObject();
    up_axis_ = new VertexRenderObject();
    up_triangle_ = new VertexRenderObject();
    up_grass_ = new VertexRenderObject();
    up_cube_ = new VertexRenderObject();

    up_grid_->Initialize(
            sizeof(GameData::kGridVertices),
            (void *) GameData::kGridVertices,
            PositionVertexSpecification{
                    up_grid_shader_->GetAttribVariableLocation("position")
            },
            up_grid_shader_,
            up_grid_shader_uniform_,
            GL_STATIC_DRAW,
            GL_LINES,
            22 * 2);
    up_axis_->Initialize(
            GameData::kAxisVerticesSize,
            (void *) GameData::kAxisVertices,
            ColorVertexSpecification{
                    up_shader_->GetAttribVariableLocation("position"),
                    up_shader_->GetAttribVariableLocation("color")
            },
            up_shader_,
            up_axis_shader_uniform_,
            GL_STATIC_DRAW,
            GL_LINES,
            6);
    up_triangle_->Initialize(
            sizeof(kVertices),
            (void *) kVertices,
            ColorVertexSpecification{
                    up_shader_->GetAttribVariableLocation("position"),
                    up_shader_->GetAttribVariableLocation("color")
            },
            up_shader_,
            up_triangle_shader_uniform_,
            GL_STATIC_DRAW,
            GL_TRIANGLES,
            3);
    up_grass_->Initialize(
            sizeof(kGrassVertices),
            (void *) kGrassVertices,
            TextureVertexSpecification{
                    up_texture_shader_->GetAttribVariableLocation("position"),
                    up_texture_shader_->GetAttribVariableLocation("texcoord")
            },
            up_texture_shader_,
            up_grass_shader_uniform_,
            GL_STATIC_DRAW,
            GL_TRIANGLE_STRIP,
            4);

    up_cube_->Initialize(
            sizeof(GameData::kCubeVertices),
            (void *) GameData::kCubeVertices,
            PositionVertexSpecification{
                    up_grid_shader_->GetAttribVariableLocation("position")
            },
            up_grid_shader_,
            up_cube_shader_uniform_,
            GL_STATIC_DRAW,
            GL_TRIANGLES,
            36);

    // Projection 行列を設定
    const glm::mat4 projection_mat = glm::perspective(glm::radians(45.0f), 8.f / 6.f, 1.f, 50.0f);
    up_grid_shader_uniform_->SetProjectionMat(projection_mat);
    up_axis_shader_uniform_->SetProjectionMat(projection_mat);
    up_triangle_shader_uniform_->SetProjectionMat(projection_mat);
    up_grass_shader_uniform_->SetProjectionMat(projection_mat);
    up_cube_shader_uniform_->SetProjectionMat(projection_mat);
}

void SandboxScene::OnFrame() {
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    angle_ += glm::pi<float>() * 0.25f * (float) GetFrame().GetDeltaTime();

    // View 行列を設定
    const glm::mat4 view_mat = glm::lookAt(
            glm::vec3(glm::cos(angle_) * 8.0f, 1.f, glm::sin(angle_) * 12.0f),
            glm::vec3(0.f, 0.f, 0.f),
            glm::vec3(0.f, 1.f, 0.f));


    glm::mat4 model_mat = glm::mat4(1.0f);
    model_mat = glm::translate(model_mat, glm::vec3(0.0f, 0.5f, 0.0f));
    up_triangle_shader_uniform_->SetViewMat(view_mat);
    up_triangle_shader_uniform_->SetModelMat(model_mat);
    up_triangle_->Render();


    up_grid_shader_uniform_->SetViewMat(view_mat);
    up_grid_shader_uniform_->SetModelMat(glm::mat4(1.0f));
    up_grid_->Render();

    up_axis_shader_uniform_->SetViewMat(view_mat);
    up_axis_shader_uniform_->SetModelMat(glm::mat4(1.0f));
    up_axis_->Render();

    glm::mat4 grass_model_mat = glm::mat4(1.0f);
    grass_model_mat = glm::translate(grass_model_mat, glm::vec3(0.0f, 1.f, 0.3f));
    grass_model_mat = glm::scale(grass_model_mat, glm::vec3(2.0f, 2.f, 2.f));
    up_grass_shader_uniform_->SetViewMat(view_mat);
    up_grass_shader_uniform_->SetModelMat(grass_model_mat);
    up_grass_->Render();

    glm::mat4 cube_mat = glm::mat4(1.0f);
    cube_mat = glm::translate(cube_mat, glm::vec3(0.0f, 2.f, 0.0f));
    cube_mat = glm::scale(cube_mat, glm::vec3(0.5, 0.5, 0.5));
    up_cube_shader_uniform_->SetViewMat(view_mat);
    up_cube_shader_uniform_->SetModelMat(cube_mat);
    up_cube_->Render();
}

void SandboxScene::OnDestroy() {
    texture_grass_.Finalize();
    texture_bitmap_font_.Finalize();

    FINALIZE_AND_DELETE(up_bitmap_font_render_);

    SAFE_DELETE(up_grid_shader_uniform_);
    SAFE_DELETE(up_axis_shader_uniform_);
    SAFE_DELETE(up_triangle_shader_uniform_);
    SAFE_DELETE(up_grass_shader_uniform_);
    SAFE_DELETE(up_cube_shader_uniform_);

    FINALIZE_AND_DELETE(up_grid_);
    FINALIZE_AND_DELETE(up_axis_);
    FINALIZE_AND_DELETE(up_triangle_);
    FINALIZE_AND_DELETE(up_grass_);
    FINALIZE_AND_DELETE(up_cube_);

    FINALIZE_AND_DELETE(up_grid_shader_);
    FINALIZE_AND_DELETE(up_shader_);
    FINALIZE_AND_DELETE(up_texture_shader_);
    FINALIZE_AND_DELETE(up_texture_2d_shader_);
}

void SandboxScene::OnKey(int glfw_key, int glfw_action) {
    // ESC の場合はとりあえずアプリケーションを終了する
    if (glfw_key == GLFW_KEY_ESCAPE && glfw_action == GLFW_PRESS) {
        should_destroy_ = true;
    }
}
