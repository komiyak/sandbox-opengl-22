//
// Created by komiyak on 22/11/21.
//

#ifndef SANDBOX_OPENGL_22_VERTEX_RENDER_OBJECT_H_
#define SANDBOX_OPENGL_22_VERTEX_RENDER_OBJECT_H_

#include <glad/glad.h>
#include "base_object.h"

// 簡易的な頂点描画オブジェクト
class VertexRenderObject : public BaseObject {
public:
    // vertex_size: 頂点データのサイズ
    // vertex_data: 頂点データのポインタ
    // position_attrib_location: 頂点データの位置 (position) の attrib location
    // usage: VBO の役割
    // draw_mode: Draw コマンドのモード
    // draw_count: Draw コマンドで有効なプリミティブの数
    void Initialize(
            GLsizeiptr vertex_size,
            const void *vertex_data,
            GLenum usage,
            GLenum draw_mode,
            GLsizei draw_count,
            GLint position_attrib_location);

    void Finalize() override;

    // Emit gl draw commands.
    void Draw() const;

private:
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
};

#endif //SANDBOX_OPENGL_22_VERTEX_RENDER_OBJECT_H_
