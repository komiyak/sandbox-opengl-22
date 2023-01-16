#include "position_with_normal_and_texcoord_vertex_specification.h"

void PositionWithNormalAndTexcoordVertexSpecification::Specify() const {
    // position(x, y, z), normal vector (x, y, z), texcoord (s, t) を持つ頂点レイアウト
    glEnableVertexAttribArray(Location("position"));
    glVertexAttribPointer(Location("position"), 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), nullptr);

    const void *normal_start = (void *) (3 * sizeof(float));
    glEnableVertexAttribArray(Location("normal"));
    glVertexAttribPointer(Location("normal"), 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), normal_start);

    const void *texcoord_start = (void *) (6 * sizeof(float));
    glEnableVertexAttribArray(Location("texcoord"));
    glVertexAttribPointer(Location("texcoord"), 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), texcoord_start);
}
