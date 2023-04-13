#ifndef SANDBOX_OPENGL_22_POSITION_WITH_NORMAL_AND_TEXCOORD_VERTEX_SPECIFICATION_H_
#define SANDBOX_OPENGL_22_POSITION_WITH_NORMAL_AND_TEXCOORD_VERTEX_SPECIFICATION_H_

#include <gl_app/gl.h>
#include "vertex_specification.h"

#include <utility>

class PositionWithNormalAndTexcoordVertexSpecification : public VertexSpecification {
public:
    void Specify(const Shader &shader) const override;

    static void UseSpecification(const Shader& shader) {
        PositionWithNormalAndTexcoordVertexSpecification{}.Specify(shader);
    }
};


#endif //SANDBOX_OPENGL_22_POSITION_WITH_NORMAL_AND_TEXCOORD_VERTEX_SPECIFICATION_H_
