#ifndef SANDBOX_OPENGL_22_VERTEX_RENDER_OBJECT_H_
#define SANDBOX_OPENGL_22_VERTEX_RENDER_OBJECT_H_

#include "opengl_glfw.h"
#include "base_object.h"

class VertexSpecification;

class Shader;

class ShaderUniform;

class VertexRenderObject : public BaseObject {
public:
    // vertex_size 頂点データのサイズ
    // p_vertex_data 頂点データのポインタ
    // vertex_specification 頂点データの属性を説明する VertexSpecification オブジェクト
    // p_shader 利用する shader
    // p_shader_uniform 利用する shader uniform
    // usage VBO の役割
    // draw_mode Draw コマンドのモード
    // draw_count Draw コマンドで有効なプリミティブの数
    void Initialize(
            GLsizeiptr vertex_size,
            const void *p_vertex_data,
            const VertexSpecification &vertex_specification,
            const Shader *p_shader,
            const ShaderUniform *p_shader_uniform,
            GLenum usage,
            GLenum draw_mode,
            GLsizei draw_count);

    void Finalize() override;

    void Render() const;

private:
    // Already initialized
    bool initialized_{};

    // Vertex array object
    GLuint vao_{};
    // Vertex buffer object
    GLuint vbo_{};

    // Draw mode in the draw command.
    GLenum draw_mode_{};
    // Draw count first in the draw command.
    GLsizei draw_count_first_{};
    // Draw count in the draw command.
    GLsizei draw_count_{};

    const Shader *p_shader_{};
    const ShaderUniform *p_shader_uniform_{};
};

#endif //SANDBOX_OPENGL_22_VERTEX_RENDER_OBJECT_H_
