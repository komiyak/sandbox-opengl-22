//
// Created by komiyak on 22/11/22.
//

#include "color_vertex_specification.h"

void ColorVertexSpecification::Specify() const {
    // position(x, y, z) と color (r, g, b) を持つ頂点レイアウト
    glEnableVertexAttribArray(Location("position"));
    glVertexAttribPointer(Location("position"), 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);

    const void *color_start = (void *) (3 * sizeof(float));
    glEnableVertexAttribArray(Location("color"));
    glVertexAttribPointer(Location("color"), 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), color_start);
}
