#ifndef SANDBOX_OPENGL_22_VERTEX_SPECIFICATION_H_
#define SANDBOX_OPENGL_22_VERTEX_SPECIFICATION_H_

#include "../opengl_glfw.h"

class Shader;

class VertexSpecification {
public:
    explicit VertexSpecification(const Shader *p_shader) : p_shader_(p_shader) {}

    // 頂点データのレイアウトに関する定義を OpenGL context に送信する
    virtual void Specify() const = 0;

protected:
    GLint GetAttribVariableLocation(const char *name) const;

    GLint Location(const char *name) const {
        return GetAttribVariableLocation(name);
    }

private:
    const Shader *p_shader_{};
};

#endif //SANDBOX_OPENGL_22_VERTEX_SPECIFICATION_H_
