#ifndef SANDBOX_OPENGL_22_POSITION_VERTEX_SPECIFICATION_H_
#define SANDBOX_OPENGL_22_POSITION_VERTEX_SPECIFICATION_H_

#include <gl_app/gl.h>
#include "vertex_specification.h"

#include <utility>

class PositionVertexSpecification : public VertexSpecification {
public:
    void Specify(const Shader &shader) const override;

    static void UseSpecification(const Shader &shader) {
        PositionVertexSpecification{}.Specify(shader);
    }
};

#endif //SANDBOX_OPENGL_22_POSITION_VERTEX_SPECIFICATION_H_
