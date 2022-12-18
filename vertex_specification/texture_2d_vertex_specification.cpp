#include "texture_2d_vertex_specification.h"

void Texture2dVertexSpecification::Specify() const {
    // position(x, y) と texcoord(s, t) を持つ頂点レイアウト
    glEnableVertexAttribArray(position_attrib_location_);
    glVertexAttribPointer(position_attrib_location_, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);

    const void *color_start = (void *) (2 * sizeof(float));
    glEnableVertexAttribArray(texcoord_attrib_location_);
    glVertexAttribPointer(texcoord_attrib_location_, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), color_start);
}
