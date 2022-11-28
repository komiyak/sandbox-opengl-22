#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include "main_application.h"
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

void MainApplication::OnStart() {
    // 頂点
    // Note: Projection の説明を省くために、最初から device coordinates に対応した頂点座標としておく
    const GLfloat kVertices[] = {
            // x, y, z, r, g, b
            0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    };

    const GLfloat kAxisVertices[] = {
            // x, y, z, r, g, b
            0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

            0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,

            0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f,
    };

    const GLfloat kGridPlaneVertices[] = {
            -5.0f, 0.0f, -5.f,
            -5.0f, 0.0f, 5.0f,

            -4.0f, 0.0f, -5.0f,
            -4.0f, 0.0f, 5.0f,

            -3.0f, 0.0f, -5.0f,
            -3.0f, 0.0f, 5.0f,

            -2.0f, 0.0f, -5.0f,
            -2.0f, 0.0f, 5.0f,

            -1.0f, 0.0f, -5.0f,
            -1.0f, 0.0f, 5.0f,

            0.0f, 0.0f, -5.0f,
            0.0f, 0.0f, 5.0f,

            1.0f, 0.0f, -5.0f,
            1.0f, 0.0f, 5.0f,

            2.0f, 0.0f, -5.0f,
            2.0f, 0.0f, 5.0f,

            3.0f, 0.0f, -5.0f,
            3.0f, 0.0f, 5.0f,

            4.0f, 0.0f, -5.0f,
            4.0f, 0.0f, 5.0f,

            5.0f, 0.0f, -5.0f,
            5.0f, 0.0f, 5.0f,


            -5.0f, 0.0f, -5.0f,
            5.0f, 0.0f, -5.0f,

            -5.0f, 0.0f, -4.0f,
            5.0f, 0.0f, -4.0f,

            -5.0f, 0.0f, -3.0f,
            5.0f, 0.0f, -3.0f,

            -5.0f, 0.0f, -2.0f,
            5.0f, 0.0f, -2.0f,

            -5.0f, 0.0f, -1.0f,
            5.0f, 0.0f, -1.0f,

            -5.0f, 0.0f, 0.0f,
            5.0f, 0.0f, 0.0f,

            -5.0f, 0.0f, 1.0f,
            5.0f, 0.0f, 1.0f,

            -5.0f, 0.0f, 2.0f,
            5.0f, 0.0f, 2.0f,

            -5.0f, 0.0f, 3.0f,
            5.0f, 0.0f, 3.0f,

            -5.0f, 0.0f, 4.0f,
            5.0f, 0.0f, 4.0f,

            -5.0f, 0.0f, 5.0f,
            5.0f, 0.0f, 5.0f,
    };

    const GLfloat kGrassVertices[] = {
            // x, y, z, s, t
            -0.5f, -0.5f, 0.f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.f, 1.0f, 0.0f,
    };

    up_grid_shader_ = new Shader();
    up_grid_shader_->BuildFromFile("shader/white_vertex.vert", "shader/white_vertex.frag");

    up_shader_ = new Shader();
    up_shader_->BuildFromFile("shader/vertex_color.vert", "shader/vertex_color.frag");

    up_texture_shader_ = new Shader();
    up_texture_shader_->BuildFromFile("shader/texture.vert", "shader/texture.frag");

    glGenTextures(1, &texture_);
    glBindTexture(GL_TEXTURE_2D, texture_);

    auto *up_png_load = new PngLoad();
    up_png_load->LoadFile("./texture/grass.png", PNG_FORMAT_RGBA);
    glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            up_png_load->GetImageSize().width,
            up_png_load->GetImageSize().height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            up_png_load->GetData());
    FINALIZE_AND_DELETE(up_png_load);
    OPENGL_DEBUG_CHECK();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    up_grid_shader_uniform_ = new BasicShaderUniform{
            up_grid_shader_->GetProjectionMatUniformLocation(),
            up_grid_shader_->GetViewMatUniformLocation(),
            up_grid_shader_->GetModelMatUniformLocation()};

    up_axis_shader_uniform_ = new BasicShaderUniform{
            up_shader_->GetProjectionMatUniformLocation(),
            up_shader_->GetViewMatUniformLocation(),
            up_shader_->GetModelMatUniformLocation()};

    up_triangle_shader_uniform_ = new BasicShaderUniform{
            up_shader_->GetProjectionMatUniformLocation(),
            up_shader_->GetViewMatUniformLocation(),
            up_shader_->GetModelMatUniformLocation()};

    up_grass_shader_uniform_ = new TextureShaderUniform{
            up_texture_shader_->GetProjectionMatUniformLocation(),
            up_texture_shader_->GetViewMatUniformLocation(),
            up_texture_shader_->GetModelMatUniformLocation(),
            up_texture_shader_->GetTextureUnitUniformLocation()};

    // texture unit 0 を利用する
    up_grass_shader_uniform_->SetTextureUnit(0);

    up_grid_ = new VertexRenderObject();
    up_axis_ = new VertexRenderObject();
    up_triangle_ = new VertexRenderObject();
    up_grass_ = new VertexRenderObject();

    up_grid_->Initialize(
            sizeof(kGridPlaneVertices),
            (void *) kGridPlaneVertices,
            PositionVertexSpecification{up_grid_shader_->GetPositionAttribVariableLocation()},
            up_grid_shader_,
            up_grid_shader_uniform_,
            GL_STATIC_DRAW,
            GL_LINES,
            22 * 2);
    up_axis_->Initialize(
            sizeof(kAxisVertices),
            (void *) kAxisVertices,
            ColorVertexSpecification{
                    up_shader_->GetPositionAttribVariableLocation(),
                    up_shader_->GetColorAttribVariableLocation()},
            up_shader_,
            up_axis_shader_uniform_,
            GL_STATIC_DRAW,
            GL_LINES,
            6);
    up_triangle_->Initialize(
            sizeof(kVertices),
            (void *) kVertices,
            ColorVertexSpecification{
                    up_shader_->GetPositionAttribVariableLocation(),
                    up_shader_->GetColorAttribVariableLocation()},
            up_shader_,
            up_triangle_shader_uniform_,
            GL_STATIC_DRAW,
            GL_TRIANGLES,
            3);
    up_grass_->Initialize(
            sizeof(kGrassVertices),
            (void *) kGrassVertices,
            TextureVertexSpecification{
                    up_texture_shader_->GetPositionAttribVariableLocation(),
                    up_texture_shader_->GetTexcoordAttribVariableLocation()},
            up_texture_shader_,
            up_grass_shader_uniform_,
            GL_STATIC_DRAW,
            GL_TRIANGLE_STRIP,
            4);


    // Projection 行列を設定
    const glm::mat4 projection_mat = glm::perspective(glm::radians(45.0f), 8.f / 6.f, 1.f, 50.0f);
    up_grid_shader_uniform_->SetProjectionMat(projection_mat);
    up_axis_shader_uniform_->SetProjectionMat(projection_mat);
    up_triangle_shader_uniform_->SetProjectionMat(projection_mat);
    up_grass_shader_uniform_->SetProjectionMat(projection_mat);
}

void MainApplication::OnFrame() {
    up_frame_->StartFrame();

    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    angle_ += glm::pi<float>() * 0.25f * (float) up_frame_->GetDeltaTime();

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
}

void MainApplication::OnFrameAfterSwap() {
    up_frame_->EndFrame();
}

// Finalizing and deleting
#define DELETE(p) if (p) {delete (p); (p) = nullptr;} do {} while (0)

void MainApplication::OnDestroy() {
    glDeleteTextures(1, &texture_);

    FINALIZE_AND_DELETE(up_frame_);

    DELETE(up_grid_shader_uniform_);
    DELETE(up_axis_shader_uniform_);
    DELETE(up_triangle_shader_uniform_);
    DELETE(up_grass_shader_uniform_);

    FINALIZE_AND_DELETE(up_grid_);
    FINALIZE_AND_DELETE(up_axis_);
    FINALIZE_AND_DELETE(up_triangle_);
    FINALIZE_AND_DELETE(up_grass_);

    FINALIZE_AND_DELETE(up_grid_shader_);
    FINALIZE_AND_DELETE(up_shader_);
    FINALIZE_AND_DELETE(up_texture_shader_);
}