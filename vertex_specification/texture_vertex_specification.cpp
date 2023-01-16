#include "texture_vertex_specification.h"

void TextureVertexSpecification::Specify() const {
    // position(x, y, z) と texcoord(s, t) を持つ頂点レイアウト
    glEnableVertexAttribArray(Location("position"));
    glVertexAttribPointer(Location("position"), 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);

    const void *color_start = (void *) (3 * sizeof(float));
    glEnableVertexAttribArray(Location("texcoord"));
    glVertexAttribPointer(Location("texcoord"), 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), color_start);
}

