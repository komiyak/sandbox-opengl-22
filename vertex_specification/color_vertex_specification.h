#ifndef SANDBOX_OPENGL_22_COLOR_VERTEX_SPECIFICATION_H_
#define SANDBOX_OPENGL_22_COLOR_VERTEX_SPECIFICATION_H_

#include <gl_app/gl.h>
#include "vertex_specification.h"

#include <utility>

class ColorVertexSpecification : public VertexSpecification {
public:
    void Specify(const Shader &shader) const override;

    static void UseSpecification(const Shader &shader) {
        ColorVertexSpecification{}.Specify(shader);
    }
};

#endif //SANDBOX_OPENGL_22_COLOR_VERTEX_SPECIFICATION_H_
