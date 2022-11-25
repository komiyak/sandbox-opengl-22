#include <glm/gtc/type_ptr.hpp>
#include "opengl_debug.h"
#include "basic_shader_uniform.h"

void BasicShaderUniform::Transfer() const {
    glUniformMatrix4fv(uniform_projection_mat_, 1, GL_FALSE, glm::value_ptr(projection_mat_));
    glUniformMatrix4fv(uniform_view_mat_, 1, GL_FALSE, glm::value_ptr(view_mat_));
    glUniformMatrix4fv(uniform_model_mat_, 1, GL_FALSE, glm::value_ptr(model_mat_));
    OPENGL_DEBUG_CHECK();
}
