#ifndef SANDBOX_OPENGL_22_POSITION_WITH_NORMAL_VECTOR_VERTEX_SPECIFICATION_H_
#define SANDBOX_OPENGL_22_POSITION_WITH_NORMAL_VECTOR_VERTEX_SPECIFICATION_H_

#include <gl_app/gl.h>
#include "vertex_specification.h"

#include <utility>

class PositionWithNormalVectorVertexSpecification : public VertexSpecification {
public:
    void Specify(const Shader &shader) const override;

    static void UseSpecification(const Shader &shader) {
        PositionWithNormalVectorVertexSpecification{}.Specify(shader);
    }
};


#endif //SANDBOX_OPENGL_22_POSITION_WITH_NORMAL_VECTOR_VERTEX_SPECIFICATION_H_
