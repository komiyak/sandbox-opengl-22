//
// Created by komiyak on 22/11/21.
//

#include <glad/glad.h>

#include "vertex_render_object.h"
#include "vertex_specification.h"
#include "shader.h"

#include "opengl_debug.h"

void VertexRenderObject::Draw() const {
    glBindVertexArray(vao_);
    glDrawArrays(draw_mode_, draw_count_first_, draw_count_);
    OPENGL_DEBUG_CHECK_ERROR();
}

void VertexRenderObject::Initialize(
        GLsizeiptr vertex_size,
        const void *p_vertex_data,
        const VertexSpecification &vertex_specification,
        const Shader &shader,
        GLenum usage,
        GLenum draw_mode,
        GLsizei draw_count) {

    draw_mode_ = draw_mode;
    draw_count_ = draw_count;
    draw_count_first_ = 0; // 頂点の描画開始位置はとりあえず 0 固定で

    // Create a VAO
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    OPENGL_DEBUG_CHECK_ERROR();

    // Create a VBO
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, vertex_size, p_vertex_data, usage);
    OPENGL_DEBUG_CHECK_ERROR();

    // Specify the layout of the vertex data.
    shader.Use();
    vertex_specification.Specify();
    OPENGL_DEBUG_CHECK_ERROR();
}

void VertexRenderObject::Finalize() {
    glDeleteBuffers(1, &vbo_);
    glDeleteVertexArrays(1, &vao_);
}
