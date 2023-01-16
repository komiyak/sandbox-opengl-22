#ifndef SANDBOX_OPENGL_22_POSITION_VERTEX_SPECIFICATION_H_
#define SANDBOX_OPENGL_22_POSITION_VERTEX_SPECIFICATION_H_

#include "../opengl_glfw.h"
#include "vertex_specification.h"

class PositionVertexSpecification : public VertexSpecification {
public:
    void Specify() const override;

    static void UseSpecification(const Shader *p_shader) {
        PositionVertexSpecification{p_shader}.Specify();
    }

private:
    explicit PositionVertexSpecification(const Shader *p_shader) : VertexSpecification(p_shader) {};
};

#endif //SANDBOX_OPENGL_22_POSITION_VERTEX_SPECIFICATION_H_
