#include "texture_vertex_specification.h"

void TextureVertexSpecification::Specify() const {
    // position(x, y, z) と texcoord(s, t) を持つ頂点レイアウト
    glEnableVertexAttribArray(position_attrib_location_);
    glVertexAttribPointer(position_attrib_location_, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);

    const void *color_start = (void *) (3 * sizeof(float));
    glEnableVertexAttribArray(texcoord_attrib_location_);
    glVertexAttribPointer(texcoord_attrib_location_, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), color_start);
}

