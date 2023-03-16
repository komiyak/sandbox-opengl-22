#ifndef SANDBOX_OPENGL_22_VERTEX_RENDER_OBJECT_H_
#define SANDBOX_OPENGL_22_VERTEX_RENDER_OBJECT_H_

#include <memory>
#include "opengl_glfw.h"

class VertexSpecification;

class Shader;

class ShaderUniform;

// 頂点データ描画オブジェクト
class VertexRenderObject {
public:
    VertexRenderObject() = default;

    ~VertexRenderObject();

    VertexRenderObject(const VertexRenderObject &) = delete;

    VertexRenderObject &&operator=(const VertexRenderObject &) = delete;

    // 描画関係のデータを作成する
    // vertex_data_size 頂点データのサイズ
    // vertex_data 頂点データのポインタ
    // shader 利用する shader
    // shader_uniform 利用する shader uniform
    // use_specification 頂点データの属性を説明する VertexSpecification を指定
    // usage VBO の役割
    // draw_mode Draw コマンドのモード
    // draw_count Draw コマンドで有効なプリミティブの数
    void Create(
            GLsizeiptr vertex_data_size,
            const void *vertex_data,
            std::weak_ptr<Shader> shader,
            std::weak_ptr<ShaderUniform> shader_uniform,
            void (*use_specification)(const Shader&),
            GLenum usage,
            GLenum draw_mode,
            GLsizei draw_count);

    // 描画関係のデータを削除する
    void Destroy();

    // 描画コマンドを発行
    void Render() const;

    // 初期化後に任意の shader に切り替える
    // 頂点データの意味が変わってしまう(glVertexAttribPointer 再実行)レベルでの
    // shader の変更には対応していない
    void ChangeShader(
            std::weak_ptr<Shader> shader,
            std::weak_ptr<ShaderUniform> shader_uniform);

private:
    // VAO and VBO were created.
    bool created_{};

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

    std::weak_ptr<Shader> shader_{};
    std::weak_ptr<ShaderUniform> shader_uniform_{};
};

#endif //SANDBOX_OPENGL_22_VERTEX_RENDER_OBJECT_H_
