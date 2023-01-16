#include "position_and_normal_and_texcoord_vertex_specification.h"

void PositionAndNormalAndTexcoordVertexSpecification::Specify() const {
    // position(x, y, z), normal vector (x, y, z), texcoord (s, t) を持つ頂点レイアウト
    glEnableVertexAttribArray(Location("vertex_position"));
    glVertexAttribPointer(Location("vertex_position"), 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), nullptr);

    const void *normal_start = (void *) (3 * sizeof(float));
    glEnableVertexAttribArray(Location("vertex_normal"));
    glVertexAttribPointer(Location("vertex_normal"), 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), normal_start);

    const void *texcoord_start = (void *) (6 * sizeof(float));
    glEnableVertexAttribArray(Location("vertex_texcoord"));
    glVertexAttribPointer(Location("vertex_texcoord"), 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), texcoord_start);
}
