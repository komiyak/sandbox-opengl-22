#include <gl_app/gl_debug.h>
#include "texture_2d_shader_uniform.h"

void Texture2dShaderUniform::Transfer() const {
    glUniform1i(uniform_texture_unit_, texture_unit_);
    glUniform2f(uniform_translation_vec_, translation_.x, translation_.y);
    glUniform2f(uniform_scaling_vec_, scaling_.x, scaling_.y);
    glUniform2f(uniform_texcoord_translation_vec_, texcoord_translation_.x, texcoord_translation_.y);
    glUniform2f(uniform_texcoord_scaling_vec_, texcoord_scaling_.x, texcoord_scaling_.y);
    GL_APP_CHECK_GL_ERROR();
}
