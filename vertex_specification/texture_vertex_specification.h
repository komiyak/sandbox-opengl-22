#ifndef SANDBOX_OPENGL_22_TEXTURE_VERTEX_SPECIFICATION_H_
#define SANDBOX_OPENGL_22_TEXTURE_VERTEX_SPECIFICATION_H_

#include "../opengl_glfw.h"
#include "vertex_specification.h"

class TextureVertexSpecification : public VertexSpecification {
public:
    TextureVertexSpecification(GLint position_attrib_location, GLint texcoord_attrib_location)
            : position_attrib_location_(position_attrib_location),
              texcoord_attrib_location_(texcoord_attrib_location) {}

    void Specify() const override;

private:
    // shader に含まれる 'position' の属性変数の位置
    GLint position_attrib_location_{};
    // shader に含まれる 'texcoord' の属性変数の位置
    GLint texcoord_attrib_location_{};
};


#endif //SANDBOX_OPENGL_22_TEXTURE_VERTEX_SPECIFICATION_H_
