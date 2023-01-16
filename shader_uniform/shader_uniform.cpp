#include "shader_uniform.h"
#include "../shader.h"

GLint ShaderUniform::GetUniformVariableLocation(const char *key) const {
    if (p_shader_) {
        return p_shader_->GetUniformVariableLocation(key);
    }
    return -1;
}

