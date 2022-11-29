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
#include "texture_2d_vertex_specification.h"
#include "basic_shader_uniform.h"
#include "texture_shader_uniform.h"
#include "texture_2d_shader_uniform.h"
#include "png_load.h"
#include "game_data.h"
#include "math.h"

void MainApplication::OnStart() {
    // 頂点
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

    up_texture_2d_shader_ = new Shader();
    up_texture_2d_shader_->BuildFromFile("shader/texture_2d.vert", "shader/texture_2d.frag");


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
    png_load_2d.LoadFile("./texture/texture_rgb_128x128.png", PNG_FORMAT_RGB);
    glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGB,
            png_load_2d.GetImageSize().width,
            png_load_2d.GetImageSize().height,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            png_load_2d.GetData());
    png_load_2d.Finalize();
    OPENGL_DEBUG_CHECK();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

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

    up_test_2d_shader_uniform_ = new Texture2dShaderUniform{
            up_texture_2d_shader_->GetTextureUnitUniformLocation(),
            up_texture_2d_shader_->GetTranslationVecUniformLocation(),
            up_texture_2d_shader_->GetScalingVecUniformLocation(),
            up_texture_2d_shader_->GetTexcoordTranslationVecUniformLocation(),
            up_texture_2d_shader_->GetTexcoordScalingVecUniformLocation()};

    // texture unit 0 を利用する
    up_grass_shader_uniform_->SetTextureUnit(0);
    // 2d 描画は texture unit 1 を利用
    up_test_2d_shader_uniform_->SetTextureUnit(1);


    // 2d の位置を適当に決定
    up_test_2d_shader_uniform_->SetTranslation(
            math::TransformFromScreenCoordinateToDeviceCoordinate(
                    10.f, 10.f, p_context_->GetWindowScreenWidth(), p_context_->GetWindowScreenHeight()));
    // スクリーンの半分のサイズに設定
    up_test_2d_shader_uniform_->SetScaling(
            glm::vec2(
                    100.0f / p_context_->GetWindowScreenWidth() * 2.f,
                    100.0f / p_context_->GetWindowScreenHeight() * 2.f));

    // texcoord をずらしてみる(test)
    up_test_2d_shader_uniform_->SetTexcoordScaling(glm::vec2(0.5f, 0.5f));
    up_test_2d_shader_uniform_->SetTexcoordTranslation(glm::vec2(0.5f, 0.5f));


    up_grid_ = new VertexRenderObject();
    up_axis_ = new VertexRenderObject();
    up_triangle_ = new VertexRenderObject();
    up_grass_ = new VertexRenderObject();
    up_test_2d_ = new VertexRenderObject();

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
    up_test_2d_->Initialize(
            sizeof(GameData::kQuad2dPivotTopLeftVertices),
            (void *) GameData::kQuad2dPivotTopLeftVertices,
            Texture2dVertexSpecification{
                    up_texture_2d_shader_->GetPositionAttribVariableLocation(),
                    up_texture_2d_shader_->GetTexcoordAttribVariableLocation()},
            up_texture_2d_shader_,
            up_test_2d_shader_uniform_,
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

    // 2d 描画テスト
    up_test_2d_->Render();
}

void MainApplication::OnFrameAfterSwap() {
    up_frame_->EndFrame();
}

// Finalizing and deleting
#define DELETE(p) if (p) {delete (p); (p) = nullptr;} do {} while (0)

void MainApplication::OnDestroy() {
    glDeleteTextures(1, &texture_0_);
    glDeleteTextures(1, &texture_1_);

    FINALIZE_AND_DELETE(up_frame_);

    DELETE(up_grid_shader_uniform_);
    DELETE(up_axis_shader_uniform_);
    DELETE(up_triangle_shader_uniform_);
    DELETE(up_grass_shader_uniform_);
    DELETE(up_test_2d_shader_uniform_);

    FINALIZE_AND_DELETE(up_grid_);
    FINALIZE_AND_DELETE(up_axis_);
    FINALIZE_AND_DELETE(up_triangle_);
    FINALIZE_AND_DELETE(up_grass_);
    FINALIZE_AND_DELETE(up_test_2d_);

    FINALIZE_AND_DELETE(up_grid_shader_);
    FINALIZE_AND_DELETE(up_shader_);
    FINALIZE_AND_DELETE(up_texture_shader_);
    FINALIZE_AND_DELETE(up_texture_2d_shader_);
}
