#include "position_with_normal_and_texcoord_vertex_specification.h"

void PositionWithNormalAndTexcoordVertexSpecification::Specify(const Shader &shader) const {
    // position(x, y, z), normal vector (x, y, z), texcoord (s, t) を持つ頂点レイアウト
    glEnableVertexAttribArray(Location(shader, "position"));
    glVertexAttribPointer(Location(shader, "position"), 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), nullptr);

    const void *normal_start = (void *) (3 * sizeof(float));
    glEnableVertexAttribArray(Location(shader, "normal"));
    glVertexAttribPointer(Location(shader, "normal"), 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), normal_start);

    const void *texcoord_start = (void *) (6 * sizeof(float));
    glEnableVertexAttribArray(Location(shader, "texcoord"));
    glVertexAttribPointer(Location(shader, "texcoord"), 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), texcoord_start);
}
