#include <glm/gtc/type_ptr.hpp>

#include "sample_lighting_cube_shader_uniform.h"
#include "opengl_debug.h"

void SampleLightingCubeShaderUniform::Transfer() const {
    glUniformMatrix4fv(uniform_projection_mat_, 1, GL_FALSE, glm::value_ptr(projection_mat_));
    glUniformMatrix4fv(uniform_view_mat_, 1, GL_FALSE, glm::value_ptr(view_mat_));
    glUniformMatrix4fv(uniform_model_mat_, 1, GL_FALSE, glm::value_ptr(model_mat_));
    glUniform3f(uniform_object_color_, object_color_.x, object_color_.y, object_color_.z);
    glUniform3f(uniform_light_color_, light_color_.x, light_color_.y, light_color_.z);
    OPENGL_DEBUG_CHECK();
}
