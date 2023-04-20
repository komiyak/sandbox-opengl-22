#include <gl_app/debug_util.h>
#include "font_shader_uniform.h"

void FontShaderUniform::Transfer() const {
    glUniform1i(Location("tex"), texture_unit_);
    glUniform2f(Location("translation_vec"), translation_.x, translation_.y);
    glUniform2f(Location("scaling_vec"), scaling_.x, scaling_.y);
    glUniform2f(Location("texcoord_translation_vec"), texcoord_translation_.x, texcoord_translation_.y);
    glUniform2f(Location("texcoord_scaling_vec"), texcoord_scaling_.x, texcoord_scaling_.y);
    glUniform3f(Location("color"), color_.x, color_.y, color_.z);
    GL_APP_CHECK_GL_ERROR();
}
