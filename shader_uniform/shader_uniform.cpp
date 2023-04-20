#include "shader_uniform.h"
#include "../shader.h"

GLint ShaderUniform::GetUniformVariableLocation(const std::string &key) const {
    if (auto shader = shader_.lock()) {
        return shader->GetUniformVariableLocation(key);
    }
    return -1;
}
