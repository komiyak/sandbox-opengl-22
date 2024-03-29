#include <gl_app/gl_debug.h>
#include <glm/gtc/type_ptr.hpp>

#include "texture_shader_uniform.h"

void TextureShaderUniform::Transfer() const {
    glUniformMatrix4fv(Location("projection_mat"), 1, GL_FALSE, glm::value_ptr(projection_mat_));
    glUniformMatrix4fv(Location("view_mat"), 1, GL_FALSE, glm::value_ptr(view_mat_));
    glUniformMatrix4fv(Location("model_mat"), 1, GL_FALSE, glm::value_ptr(model_mat_));
    glUniform1i(Location("tex"), texture_unit_);
    GL_APP_CHECK_GL_ERROR();
}

