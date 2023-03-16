#include "position_with_normal_vector_vertex_specification.h"

void PositionWithNormalVectorVertexSpecification::Specify(const Shader &shader) const {
    // position(x, y, z) と normal vector (x, y, z) を持つ頂点レイアウト
    glEnableVertexAttribArray(Location(shader, "position"));
    glVertexAttribPointer(Location(shader, "position"), 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);

    const void *normal_start = (void *) (3 * sizeof(float));
    glEnableVertexAttribArray(Location(shader, "normal"));
    glVertexAttribPointer(Location(shader, "normal"), 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), normal_start);
}
