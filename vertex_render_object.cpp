#include "vertex_render_object.h"

#include <utility>
#include <iostream>
#include "opengl_debug.h"
#include "debug.h"
#include "shader.h"
#include "shader_uniform/shader_uniform.h"

void VertexRenderObject::Create(
        GLsizeiptr vertex_data_size,
        const void *vertex_data,
        std::weak_ptr<Shader> shader,
        std::weak_ptr<ShaderUniform> shader_uniform,
        void (*use_specification)(const Shader&),
        GLenum usage,
        GLenum draw_mode,
        GLsizei draw_count) {

    if (created_) return;

    created_ = true;
    shader_ = std::move(shader);
    shader_uniform_ = std::move(shader_uniform);
    draw_mode_ = draw_mode;
    draw_count_ = draw_count;
    draw_count_first_ = 0; // 頂点の描画開始位置はとりあえず 0 固定で

    // Create a VAO
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    OPENGL_DEBUG_CHECK();

    // Create a VBO
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    OPENGL_DEBUG_CHECK();
    glBufferData(GL_ARRAY_BUFFER, vertex_data_size, vertex_data, usage);
    OPENGL_DEBUG_CHECK();

    // Specify the layout of the vertex data.
    if (auto p = shader_.lock()) {
        p->UseProgram();
        use_specification(*p);
    } else {
        shader_.reset();
    }
}

void VertexRenderObject::Destroy() {
    if (created_) {
        glDeleteBuffers(1, &vbo_);
        glDeleteVertexArrays(1, &vao_);
        vbo_ = 0;
        vao_ = 0;
        shader_.reset();
        shader_uniform_.reset();
    }
    created_ = false;
}

void VertexRenderObject::Render() const {
    if (!created_) return;

    if (auto shader = shader_.lock()) {
        // shader 適用
        shader->UseProgram();
        if (auto shader_uniform = shader_uniform_.lock()) {
            if (shader_uniform->IsActivated()) {
                shader_uniform->Transfer();
            }

            // shader uniform の設定は正しいのに、activate を忘れているときがあるので、
            // activate されてない場合は停止する。
            DEBUG_ASSERT_MESSAGE(shader_uniform->IsActivated(),
                                 "Found a not activated shader uniform. It must be activated.");
        }

        // draw 実行
        glBindVertexArray(vao_);
        OPENGL_DEBUG_CHECK();
        glDrawArrays(draw_mode_, draw_count_first_, draw_count_);
        OPENGL_DEBUG_CHECK();
    }
}

void VertexRenderObject::ChangeShader(
        std::weak_ptr<Shader> shader,
        std::weak_ptr<ShaderUniform> shader_uniform) {
    DEBUG_ASSERT(created_);
    if (!created_) return;

    shader_ = std::move(shader);
    shader_uniform_ = std::move(shader_uniform);
}

VertexRenderObject::~VertexRenderObject() {
    try {
        Destroy();
    } catch (...) {
        std::cerr << "(VertexRenderObject) Fatal error in destructor." << std::endl;
    }
}

