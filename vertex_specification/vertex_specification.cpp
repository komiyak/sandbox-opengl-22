#include "vertex_specification.h"
#include "../shader.h"

GLint VertexSpecification::GetAttribVariableLocation(const char *name) const {
    if (p_shader_) {
        return p_shader_->GetAttribVariableLocation(name);
    }
    return -1;
}
