#include "vertex_render_object.h"
#include "opengl_debug.h"
#include "debug.h"
#include "shader.h"
#include "shader_uniform/shader_uniform.h"

void VertexRenderObject::Initialize(
        GLsizeiptr vertex_size,
        const void *p_vertex_data,
        const Shader *p_shader,
        const ShaderUniform *p_shader_uniform,
        void (*use_specification)(const Shader *),
        GLenum usage,
        GLenum draw_mode,
        GLsizei draw_count) {

    DEBUG_ASSERT(p_shader);

    initialized_ = true;
    p_shader_ = p_shader;
    p_shader_uniform_ = p_shader_uniform;
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
    glBufferData(GL_ARRAY_BUFFER, vertex_size, p_vertex_data, usage);
    OPENGL_DEBUG_CHECK();

    // Specify the layout of the vertex data.
    p_shader_->UseProgram();
    use_specification(p_shader_);
}

void VertexRenderObject::Finalize() {
    if (initialized_) {
        glDeleteBuffers(1, &vbo_);
        glDeleteVertexArrays(1, &vao_);
        vbo_ = 0;
        vao_ = 0;
        p_shader_ = nullptr;
        p_shader_uniform_ = nullptr;
    }
    initialized_ = false;
}

void VertexRenderObject::Render() const {
    if (!initialized_) return;

    if (p_shader_) {
        // shader 適用
        p_shader_->UseProgram();
        if (p_shader_uniform_ && p_shader_uniform_->IsActivated()) {
            p_shader_uniform_->Transfer();
        }
        // shader uniform の設定は正しいのに、activate を忘れているときがあるので、
        // activate されてない場合は停止する。
        DEBUG_ASSERT_MESSAGE(p_shader_ && p_shader_uniform_ && p_shader_uniform_->IsActivated(),
                             "Found a not activated shader uniform. It must be activated.");

        // draw 実行
        glBindVertexArray(vao_);
        OPENGL_DEBUG_CHECK();
        glDrawArrays(draw_mode_, draw_count_first_, draw_count_);
        OPENGL_DEBUG_CHECK();
    }
}

void VertexRenderObject::ChangeShader(
        const Shader *p_shader,
        const ShaderUniform *p_shader_uniform) {
    DEBUG_ASSERT(initialized_);
    DEBUG_ASSERT(p_shader);
    DEBUG_ASSERT(p_shader_uniform);
    if (!initialized_) return;

    p_shader_ = p_shader;
    p_shader_uniform_ = p_shader_uniform;
}

