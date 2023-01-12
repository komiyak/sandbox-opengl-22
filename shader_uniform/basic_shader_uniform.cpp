#include <glm/gtc/type_ptr.hpp>

#include "basic_shader_uniform.h"
#include "../opengl_debug.h"

void BasicShaderUniform::Transfer() const {
    glUniformMatrix4fv(GetUniformVariableLocation("projection_mat"), 1, GL_FALSE, glm::value_ptr(projection_mat_));
    glUniformMatrix4fv(GetUniformVariableLocation("view_mat"), 1, GL_FALSE, glm::value_ptr(view_mat_));
    glUniformMatrix4fv(GetUniformVariableLocation("model_mat"), 1, GL_FALSE, glm::value_ptr(model_mat_));
    OPENGL_DEBUG_CHECK();
}
