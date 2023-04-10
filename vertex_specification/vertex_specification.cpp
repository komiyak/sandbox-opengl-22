#include "vertex_specification.h"
#include "../shader.h"

GLint VertexSpecification::Location(const Shader &shader, const std::string &name) {
    return shader.GetAttribVariableLocation(name);
}
