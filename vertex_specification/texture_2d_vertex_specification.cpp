#include "texture_2d_vertex_specification.h"

void Texture2dVertexSpecification::Specify() const {
    // position(x, y) と texcoord(s, t) を持つ頂点レイアウト
    glEnableVertexAttribArray(Location("position"));
    glVertexAttribPointer(Location("position"), 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);

    const void *color_start = (void *) (2 * sizeof(float));
    glEnableVertexAttribArray(Location("texcoord"));
    glVertexAttribPointer(Location("texcoord"), 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), color_start);
}
