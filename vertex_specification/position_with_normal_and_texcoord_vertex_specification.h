#ifndef SANDBOX_OPENGL_22_POSITION_WITH_NORMAL_AND_TEXCOORD_VERTEX_SPECIFICATION_H_
#define SANDBOX_OPENGL_22_POSITION_WITH_NORMAL_AND_TEXCOORD_VERTEX_SPECIFICATION_H_

#include "../opengl_glfw.h"
#include "vertex_specification.h"

class PositionWithNormalAndTexcoordVertexSpecification : public VertexSpecification {
public:
    void Specify() const override;

    static void UseSpecification(const Shader *p_shader) {
        PositionWithNormalAndTexcoordVertexSpecification{p_shader}.Specify();
    }

private:
    explicit PositionWithNormalAndTexcoordVertexSpecification(const Shader *p_shader) : VertexSpecification(p_shader) {}
};


#endif //SANDBOX_OPENGL_22_POSITION_WITH_NORMAL_AND_TEXCOORD_VERTEX_SPECIFICATION_H_
