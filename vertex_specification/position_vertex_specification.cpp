#include "position_vertex_specification.h"

void PositionVertexSpecification::Specify(const Shader &shader) const {
    // position(x, y, z) だけを持つ頂点レイアウト
    glEnableVertexAttribArray(Location(shader, "position"));
    glVertexAttribPointer(Location(shader, "position"), 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}
