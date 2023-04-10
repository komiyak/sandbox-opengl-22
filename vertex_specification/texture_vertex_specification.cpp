#include "texture_vertex_specification.h"

void TextureVertexSpecification::Specify(const Shader &shader) const {
    // position(x, y, z) と texcoord(s, t) を持つ頂点レイアウト
    glEnableVertexAttribArray(Location(shader, "position"));
    glVertexAttribPointer(Location(shader, "position"), 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);

    const void *color_start = (void *) (3 * sizeof(float));
    glEnableVertexAttribArray(Location(shader, "texcoord"));
    glVertexAttribPointer(Location(shader, "texcoord"), 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), color_start);
}

