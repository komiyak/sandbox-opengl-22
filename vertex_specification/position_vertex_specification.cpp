//
// Created by komiyak on 22/11/22.
//

#include "position_vertex_specification.h"

void PositionVertexSpecification::Specify() const {
    // position(x, y, z) だけを持つ頂点レイアウト
    glEnableVertexAttribArray(position_attrib_location_);
    glVertexAttribPointer(position_attrib_location_, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

