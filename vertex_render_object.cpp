//
// Created by komiyak on 22/11/21.
//

#include <glad/glad.h>
#include "vertex_render_object.h"

void VertexRenderObject::Draw() const {
    glBindVertexArray(vao_);
    glDrawArrays(draw_mode_, draw_count_first_, draw_count_);
}

void VertexRenderObject::Initialize(
        GLsizeiptr vertex_size,
        const void *vertex_data,
        GLenum usage,
        GLenum draw_mode,
        GLsizei draw_count,
        GLint position_attrib_location) {

    draw_mode_ = draw_mode;
    draw_count_ = draw_count;
    draw_count_first_ = 0; // 頂点の描画開始位置はとりあえず 0 固定で

    // Create a VAO
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    // Create a VBO
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, vertex_size, vertex_data, usage);

    // Specify the layout of the vertex data
    glEnableVertexAttribArray(position_attrib_location);
    glVertexAttribPointer(position_attrib_location, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void VertexRenderObject::Finalize() {
    glDeleteBuffers(1, &vbo_);
    glDeleteVertexArrays(1, &vao_);
}
