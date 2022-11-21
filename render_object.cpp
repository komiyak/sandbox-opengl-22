//
// Created by komiyak on 22/11/21.
//

#include <glad/glad.h>
#include "render_object.h"
#include "shader.h"

void RenderObject::Render() const {
    glDrawArrays(draw_mode_, draw_count_first_, draw_count_);
}

void RenderObject::BindRender() {
    glBindVertexArray(vao_);

    if (p_shader_) {
        p_shader_->Use();
    }
}

void RenderObject::Initialize(
        GLsizeiptr vertex_size,
        const void *vertex_data,
        GLenum usage,
        GLenum draw_mode,
        GLsizei draw_count,
        Shader *p_shader) {

    draw_mode_ = draw_mode;
    draw_count_ = draw_count;
    draw_count_first_ = 0; // 頂点の描画開始位置はとりあえず 0 固定で
    p_shader_ = p_shader;

    // Create a VAO
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    // Create a VBO
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, vertex_size, vertex_data, usage);

    // Specify the layout of the vertex data
    if (p_shader_) {
        GLint position_attrib = p_shader_->GetPositionAttribLocation();
        glEnableVertexAttribArray(position_attrib);
        glVertexAttribPointer(position_attrib, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    }
}

void RenderObject::Finalize() {
    glDeleteBuffers(1, &vbo_);
    glDeleteVertexArrays(1, &vao_);
    p_shader_ = nullptr;
}
