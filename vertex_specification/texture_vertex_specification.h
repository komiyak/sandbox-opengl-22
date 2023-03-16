#ifndef SANDBOX_OPENGL_22_TEXTURE_VERTEX_SPECIFICATION_H_
#define SANDBOX_OPENGL_22_TEXTURE_VERTEX_SPECIFICATION_H_

#include "../opengl_glfw.h"
#include "vertex_specification.h"

class TextureVertexSpecification : public VertexSpecification {
public:
    void Specify(const Shader &shader) const override;

    static void UseSpecification(const Shader& shader) {
        TextureVertexSpecification{}.Specify(shader);
    }
};

#endif //SANDBOX_OPENGL_22_TEXTURE_VERTEX_SPECIFICATION_H_
