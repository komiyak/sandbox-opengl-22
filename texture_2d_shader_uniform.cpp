#include "texture_2d_shader_uniform.h"
#include "opengl_debug.h"

void Texture2dShaderUniform::Transfer() const {
    glUniform1i(uniform_texture_unit_, texture_unit_);
    OPENGL_DEBUG_CHECK();
}

