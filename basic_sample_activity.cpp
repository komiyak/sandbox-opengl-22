#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include "basic_sample_activity.h"
#include "opengl_debug.h"
#include "frame.h"
#include "vertex_render_object.h"
#include "shader.h"
#include "position_vertex_specification.h"
#include "color_vertex_specification.h"
#include "texture_vertex_specification.h"
#include "basic_shader_uniform.h"
#include "texture_shader_uniform.h"
#include "png_load.h"
#include "bitmap_font_render.h"
#include "game_data.h"
#include "shader_data.h"

void BasicSampleActivity::OnStart() {
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
            "shader/white_vertex.frag",
            shader_data::kAttribVariableLocationsOfWhiteVertexShader,
            shader_data::kAttribVariableLocationsOfWhiteVertexShaderSize,
            shader_data::kUniformVariableLocationsOfWhiteVertexShader,
            shader_data::kUniformVariableLocationsOfWhiteVertexShaderSize);

    up_shader_ = new Shader();
    up_shader_->BuildFromFile(
            "shader/vertex_color.vert",
            "shader/vertex_color.frag",
            shader_data::kAttribVariableLocationsOfVertexColorShader,
            shader_data::kAttribVariableLocationsOfVertexColorShaderSize,
            shader_data::kUniformVariableLocationsOfVertexColorShader,
            shader_data::kUniformVariableLocationsOfVertexColorShaderSize);

    up_texture_shader_ = new Shader();
    up_texture_shader_->BuildFromFile(
            "shader/texture.vert",
            "shader/texture.frag",
            shader_data::kAttribVariableLocationsOfTextureShader,
            shader_data::kAttribVariableLocationsOfTextureShaderSize,
            shader_data::kUniformVariableLocationsOfTextureShader,
            shader_data::kUniformVariableLocationsOfTextureShaderSize);

    up_texture_2d_shader_ = new Shader();
    up_texture_2d_shader_->BuildFromFile(
            "shader/texture_2d.vert",
            "shader/texture_2d.frag",
            shader_data::kAttribVariableLocationsOfTexture2dShader,
            shader_data::kAttribVariableLocationsOfTexture2dShaderSize,
            shader_data::kUniformVariableLocationsOfTexture2dShader,
            shader_data::kUniformVariableLocationsOfTexture2dShaderSize);


    glGenTextures(1, &texture_0_);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_0_);

    PngLoad png_load{};
    png_load.LoadFile("./texture/grass.png", PNG_FORMAT_RGBA);
    glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            png_load.GetImageSize().width,
            png_load.GetImageSize().height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            png_load.GetData());
    png_load.Finalize();
    OPENGL_DEBUG_CHECK();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glGenTextures(1, &texture_1_);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture_1_);

    PngLoad png_load_2d{};
    png_load_2d.LoadFile("./texture/ascii_bitmap_font.png", PNG_FORMAT_RGBA);
    glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            png_load_2d.GetImageSize().width,
            png_load_2d.GetImageSize().height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            png_load_2d.GetData());
    OPENGL_DEBUG_CHECK();

    // フォント準備
    png_load_2d.Finalize();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

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
            sizeof(GameData::kCube),
            (void *) GameData::kCube,
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

void BasicSampleActivity::OnFrame() {
    frame_.StartFrame();

    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    angle_ += glm::pi<float>() * 0.25f * (float) frame_.GetDeltaTime();

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

void BasicSampleActivity::OnFrameAfterSwap() {
    frame_.EndFrame();
}

void BasicSampleActivity::OnDestroy() {
    glDeleteTextures(1, &texture_0_);
    glDeleteTextures(1, &texture_1_);

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

void BasicSampleActivity::OnKey(int glfw_key, int glfw_action) {
    // ESC の場合はとりあえずアプリケーションを終了する
    if (glfw_key == GLFW_KEY_ESCAPE && glfw_action == GLFW_PRESS) {
        should_destroy_ = true;
    }
}
