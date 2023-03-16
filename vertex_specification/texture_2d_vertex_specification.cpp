#include "texture_2d_vertex_specification.h"

void Texture2dVertexSpecification::Specify(const Shader &shader) const {
    // position(x, y) と texcoord(s, t) を持つ頂点レイアウト
    glEnableVertexAttribArray(Location(shader, "position"));
    glVertexAttribPointer(Location(shader, "position"), 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);

    const void *color_start = (void *) (2 * sizeof(float));
    glEnableVertexAttribArray(Location(shader, "texcoord"));
    glVertexAttribPointer(Location(shader, "texcoord"), 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), color_start);
}
