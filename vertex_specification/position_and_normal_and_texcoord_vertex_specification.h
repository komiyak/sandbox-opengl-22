#ifndef SANDBOX_OPENGL_22_POSITION_AND_NORMAL_AND_TEXCOORD_VERTEX_SPECIFICATION_H_
#define SANDBOX_OPENGL_22_POSITION_AND_NORMAL_AND_TEXCOORD_VERTEX_SPECIFICATION_H_

#include <gl_app/gl.h>
#include "vertex_specification.h"

class PositionAndNormalAndTexcoordVertexSpecification : public VertexSpecification {
public:
    void Specify(const Shader &shader) const override;

    static void UseSpecification(const Shader &shader) {
        PositionAndNormalAndTexcoordVertexSpecification{}.Specify(shader);
    }
};


#endif //SANDBOX_OPENGL_22_POSITION_AND_NORMAL_AND_TEXCOORD_VERTEX_SPECIFICATION_H_
