#ifndef SANDBOX_OPENGL_22_POSITION_WITH_NORMAL_AND_TEXCOORD_VERTEX_SPECIFICATION_H_
#define SANDBOX_OPENGL_22_POSITION_WITH_NORMAL_AND_TEXCOORD_VERTEX_SPECIFICATION_H_

#include <glad/glad.h>
#include "vertex_specification.h"

class PositionWithNormalAndTexcoordVertexSpecification : public VertexSpecification {
public:
    PositionWithNormalAndTexcoordVertexSpecification(
            GLint position_attrib_location,
            GLint normal_attrib_location,
            GLint texcoord_attrib_location)
            : position_attrib_location_(position_attrib_location),
              normal_attrib_location_(normal_attrib_location),
              texcoord_attrib_location_(texcoord_attrib_location) {}

    void Specify() const override;

private:
    // shader に含まれる 'position' の属性変数の位置
    GLint position_attrib_location_;
    // shader に含まれる 'normal' の属性変数の位置
    GLint normal_attrib_location_;
    // shader に含まれる 'texcoord' の属性変数の位置
    GLint texcoord_attrib_location_;
};


#endif //SANDBOX_OPENGL_22_POSITION_WITH_NORMAL_AND_TEXCOORD_VERTEX_SPECIFICATION_H_
