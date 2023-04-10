#ifndef SANDBOX_OPENGL_22_TEXTURE_2D_VERTEX_SPECIFICATION_H_
#define SANDBOX_OPENGL_22_TEXTURE_2D_VERTEX_SPECIFICATION_H_

#include "../opengl_glfw.h"
#include "vertex_specification.h"

#include <utility>

class Texture2dVertexSpecification : public VertexSpecification {
public:
    void Specify(const Shader &shader) const override;

    static void UseSpecification(const Shader &shader) {
        Texture2dVertexSpecification{}.Specify(shader);
    }
};

#endif //SANDBOX_OPENGL_22_TEXTURE_2D_VERTEX_SPECIFICATION_H_
