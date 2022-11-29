#include "texture_2d_shader_uniform.h"
#include "opengl_debug.h"

void Texture2dShaderUniform::Transfer() const {
    glUniform1i(uniform_texture_unit_, texture_unit_);
    glUniform2f(uniform_translation_vec_, translation_.x, translation_.y);
    glUniform2f(uniform_scaling_vec_, scaling_.x, scaling_.y);
    OPENGL_DEBUG_CHECK();
}

