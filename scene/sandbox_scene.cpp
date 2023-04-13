#include <gl_app/application.h>
#include <gl_app/debug_util.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "sandbox_scene.h"
#include "../vertex_specification/position_vertex_specification.h"
#include "../vertex_specification/color_vertex_specification.h"
#include "../vertex_specification/texture_vertex_specification.h"
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

    grid_shader_->BuildFromFile(
            "shader/white_vertex.vert",
            "shader/white_vertex.frag",
            "outColor");

    shader_->BuildFromFile(
            "shader/vertex_color.vert",
            "shader/vertex_color.frag",
            "outColor");

    texture_shader_->BuildFromFile(
            "shader/texture.vert",
            "shader/texture.frag",
            "outColor");

    texture_2d_shader_->BuildFromFile(
            "shader/texture_2d.vert",
            "shader/texture_2d.frag",
            "outColor");


    texture_grass_.Load(
            "./texture/grass.png",
            Texture::ImageFormat::RGBA,
            0);

    texture_bitmap_font_.Load(
            "./texture/ascii_bitmap_font.png",
            Texture::ImageFormat::RGBA,
            1);


    grid_shader_uniform_->SetShader(grid_shader_);
    axis_shader_uniform_->SetShader(shader_);
    triangle_shader_uniform_->SetShader(shader_);
    grass_shader_uniform_->SetShader(texture_shader_);
    cube_shader_uniform_->SetShader(grid_shader_);


    // texture unit 0 を利用する
    grass_shader_uniform_->SetTextureUnit(0);


    grid_.Create(
            sizeof(GameData::kGridVertices),
            (void *) GameData::kGridVertices,
            grid_shader_,
            grid_shader_uniform_,
            PositionVertexSpecification::UseSpecification,
            GL_STATIC_DRAW,
            GL_LINES,
            22 * 2);
    axis_.Create(
            GameData::kAxisVerticesSize,
            (void *) GameData::kAxisVertices,
            shader_,
            axis_shader_uniform_,
            ColorVertexSpecification::UseSpecification,
            GL_STATIC_DRAW,
            GL_LINES,
            6);
    triangle_.Create(
            sizeof(kVertices),
            (void *) kVertices,
            shader_,
            triangle_shader_uniform_,
            ColorVertexSpecification::UseSpecification,
            GL_STATIC_DRAW,
            GL_TRIANGLES,
            3);
    grass_.Create(
            sizeof(kGrassVertices),
            (void *) kGrassVertices,
            texture_shader_,
            grass_shader_uniform_,
            TextureVertexSpecification::UseSpecification,
            GL_STATIC_DRAW,
            GL_TRIANGLE_STRIP,
            4);

    cube_.Create(
            sizeof(GameData::kCubeVertices),
            (void *) GameData::kCubeVertices,
            grid_shader_,
            cube_shader_uniform_,
            PositionVertexSpecification::UseSpecification,
            GL_STATIC_DRAW,
            GL_TRIANGLES,
            36);

    // Projection 行列を設定
    const glm::mat4 projection_mat = glm::perspective(glm::radians(45.0f), 8.f / 6.f, 1.f, 50.0f);
    grid_shader_uniform_->SetProjectionMat(projection_mat);
    axis_shader_uniform_->SetProjectionMat(projection_mat);
    triangle_shader_uniform_->SetProjectionMat(projection_mat);
    grass_shader_uniform_->SetProjectionMat(projection_mat);
    cube_shader_uniform_->SetProjectionMat(projection_mat);
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
    if (triangle_shader_uniform_) {
        triangle_shader_uniform_->SetViewMat(view_mat);
        triangle_shader_uniform_->SetModelMat(model_mat);
        triangle_.Render();
    }

    if (grid_shader_uniform_) {
        grid_shader_uniform_->SetViewMat(view_mat);
        grid_shader_uniform_->SetModelMat(glm::mat4(1.0f));
        grid_.Render();
    }

    if (axis_shader_uniform_) {
        axis_shader_uniform_->SetViewMat(view_mat);
        axis_shader_uniform_->SetModelMat(glm::mat4(1.0f));
        axis_.Render();
    }

    if (grass_shader_uniform_) {
        glm::mat4 grass_model_mat = glm::mat4(1.0f);
        grass_model_mat = glm::translate(grass_model_mat, glm::vec3(0.0f, 1.f, 0.3f));
        grass_model_mat = glm::scale(grass_model_mat, glm::vec3(2.0f, 2.f, 2.f));
        grass_shader_uniform_->SetViewMat(view_mat);
        grass_shader_uniform_->SetModelMat(grass_model_mat);
        grass_.Render();
    }

    if (cube_shader_uniform_) {
        glm::mat4 cube_mat = glm::mat4(1.0f);
        cube_mat = glm::translate(cube_mat, glm::vec3(0.0f, 2.f, 0.0f));
        cube_mat = glm::scale(cube_mat, glm::vec3(0.5, 0.5, 0.5));
        cube_shader_uniform_->SetViewMat(view_mat);
        cube_shader_uniform_->SetModelMat(cube_mat);
        cube_.Render();
    }
}

void SandboxScene::OnDestroy() {}

void SandboxScene::OnKey(int glfw_key, int glfw_action) {
    // ESC の場合はとりあえずアプリケーションを終了する
    if (glfw_key == GLFW_KEY_ESCAPE && glfw_action == GLFW_PRESS) {
        SendToDestroy();
    }
}
