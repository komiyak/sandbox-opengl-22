#include "position_with_normal_and_texcoord_vertex_specification.h"

void PositionWithNormalAndTexcoordVertexSpecification::Specify() const {
    // position(x, y, z), normal vector (x, y, z), texcoord (s, t) を持つ頂点レイアウト
    glEnableVertexAttribArray(position_attrib_location_);
    glVertexAttribPointer(position_attrib_location_, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), nullptr);

    const void *normal_start = (void *) (3 * sizeof(float));
    glEnableVertexAttribArray(normal_attrib_location_);
    glVertexAttribPointer(normal_attrib_location_, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), normal_start);

    const void *texcoord_start = (void *) (6 * sizeof(float));
    glEnableVertexAttribArray(texcoord_attrib_location_);
    glVertexAttribPointer(texcoord_attrib_location_, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), texcoord_start);
}
