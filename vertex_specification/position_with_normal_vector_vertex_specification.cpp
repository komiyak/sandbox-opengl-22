#include "position_with_normal_vector_vertex_specification.h"

void PositionWithNormalVectorVertexSpecification::Specify() const {
    // position(x, y, z) と normal vector (x, y, z) を持つ頂点レイアウト
    glEnableVertexAttribArray(Location("position"));
    glVertexAttribPointer(Location("position"), 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);

    const void *normal_start = (void *) (3 * sizeof(float));
    glEnableVertexAttribArray(Location("normal"));
    glVertexAttribPointer(Location("normal"), 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), normal_start);
}
