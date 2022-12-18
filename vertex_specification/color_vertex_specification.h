#ifndef SANDBOX_OPENGL_22_COLOR_VERTEX_SPECIFICATION_H_
#define SANDBOX_OPENGL_22_COLOR_VERTEX_SPECIFICATION_H_

#include "../opengl_glfw.h"
#include "vertex_specification.h"

class ColorVertexSpecification : public VertexSpecification {
public:
    explicit ColorVertexSpecification(GLint position_attrib_location, GLint color_attrib_location)
            : position_attrib_location_(position_attrib_location),
              color_attrib_location_(color_attrib_location) {}

    void Specify() const override;

private:
    // shader に含まれる 'position' の属性変数の位置
    GLint position_attrib_location_;
    // shader に含まれる 'color' の属性変数の位置
    GLint color_attrib_location_;
};

#endif //SANDBOX_OPENGL_22_COLOR_VERTEX_SPECIFICATION_H_
