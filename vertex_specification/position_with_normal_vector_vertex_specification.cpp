#include "position_with_normal_vector_vertex_specification.h"

void PositionWithNormalVectorVertexSpecification::Specify() const {
    // position(x, y, z) と normal vector (x, y, z) を持つ頂点レイアウト
    glEnableVertexAttribArray(position_attrib_location_);
    glVertexAttribPointer(position_attrib_location_, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);

    const void *normal_start = (void *) (3 * sizeof(float));
    glEnableVertexAttribArray(normal_attrib_location_);
    glVertexAttribPointer(normal_attrib_location_, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), normal_start);
}
