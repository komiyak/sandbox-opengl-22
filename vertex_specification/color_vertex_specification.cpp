//
// Created by komiyak on 22/11/22.
//

#include "color_vertex_specification.h"
#include "../shader.h"

void ColorVertexSpecification::Specify(const Shader &shader) const {
    // position(x, y, z) と color (r, g, b) を持つ頂点レイアウト
    glEnableVertexAttribArray(Location(shader, "position"));
    glVertexAttribPointer(Location(shader, "position"), 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);

    const void *color_start = (void *) (3 * sizeof(float));
    glEnableVertexAttribArray(Location(shader, "color"));
    glVertexAttribPointer(Location(shader, "color"), 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), color_start);
}
