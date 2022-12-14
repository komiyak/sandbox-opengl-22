#include <glm/gtc/type_ptr.hpp>

#include "texture_shader_uniform.h"
#include "../opengl_debug.h"

void TextureShaderUniform::Transfer() const {
    glUniformMatrix4fv(uniform_projection_mat_, 1, GL_FALSE, glm::value_ptr(projection_mat_));
    glUniformMatrix4fv(uniform_view_mat_, 1, GL_FALSE, glm::value_ptr(view_mat_));
    glUniformMatrix4fv(uniform_model_mat_, 1, GL_FALSE, glm::value_ptr(model_mat_));
    glUniform1i(uniform_texture_unit_, texture_unit_);
    OPENGL_DEBUG_CHECK();
}

