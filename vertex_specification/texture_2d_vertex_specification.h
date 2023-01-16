#ifndef SANDBOX_OPENGL_22_TEXTURE_2D_VERTEX_SPECIFICATION_H_
#define SANDBOX_OPENGL_22_TEXTURE_2D_VERTEX_SPECIFICATION_H_

#include "../opengl_glfw.h"
#include "vertex_specification.h"

class Texture2dVertexSpecification : public VertexSpecification {
public:
    void Specify() const override;

    static void UseSpecification(const Shader *p_shader) {
        Texture2dVertexSpecification{p_shader}.Specify();
    }

private:
    Texture2dVertexSpecification(const Shader *p_shader) : VertexSpecification(p_shader) {}
};

#endif //SANDBOX_OPENGL_22_TEXTURE_2D_VERTEX_SPECIFICATION_H_
