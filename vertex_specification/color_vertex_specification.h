#ifndef SANDBOX_OPENGL_22_COLOR_VERTEX_SPECIFICATION_H_
#define SANDBOX_OPENGL_22_COLOR_VERTEX_SPECIFICATION_H_

#include "../opengl_glfw.h"
#include "vertex_specification.h"

class ColorVertexSpecification : public VertexSpecification {
public:
    void Specify() const override;

    static void UseSpecification(const Shader *p_shader) {
        ColorVertexSpecification{p_shader}.Specify();
    }

private:
    explicit ColorVertexSpecification(const Shader *p_shader) : VertexSpecification(p_shader) {};
};

#endif //SANDBOX_OPENGL_22_COLOR_VERTEX_SPECIFICATION_H_
