#ifndef SANDBOX_OPENGL_22_VERTEX_SPECIFICATION_H_
#define SANDBOX_OPENGL_22_VERTEX_SPECIFICATION_H_

#include <memory>
#include <string>
#include <utility>
#include "../opengl_glfw.h"

class Shader;

class VertexSpecification {
public:
    VertexSpecification() = default;

    virtual ~VertexSpecification() = default;

    // 頂点データのレイアウトに関する定義を OpenGL context に送信する
    virtual void Specify(const Shader &shader) const = 0;

protected:
    // Shader の GetAttribVariableLocation(name) に簡単にアクセスするためのヘルパー
    // Specify() から使うことを想定している
    [[nodiscard]] static GLint Location(const Shader &shader, const std::string &name);
};

#endif //SANDBOX_OPENGL_22_VERTEX_SPECIFICATION_H_
