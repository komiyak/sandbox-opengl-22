//
// Created by komiyak on 22/11/22.
//

#ifndef SANDBOX_OPENGL_22_VERTEX_SPECIFICATION_H_
#define SANDBOX_OPENGL_22_VERTEX_SPECIFICATION_H_

class VertexSpecification {
public:
    // 頂点データのレイアウトに関する定義を OpenGL context に送信する
    virtual void Specify() const = 0;
};

#endif //SANDBOX_OPENGL_22_VERTEX_SPECIFICATION_H_
