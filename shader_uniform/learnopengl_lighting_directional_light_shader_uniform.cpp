#include <glm/gtc/type_ptr.hpp>

#include "learnopengl_lighting_directional_light_shader_uniform.h"
#include "../opengl_debug.h"

void LearnopenglLightingDirectionalLightShaderUniform::Transfer() const {
    glUniformMatrix4fv(Location("projection_mat"), 1, GL_FALSE, glm::value_ptr(projection_mat_));
    glUniformMatrix4fv(Location("view_mat"), 1, GL_FALSE, glm::value_ptr(view_mat_));
    glUniformMatrix4fv(Location("model_mat"), 1, GL_FALSE, glm::value_ptr(model_mat_));
    glUniform3f(Location("light.direction"), light_direction_.x, light_direction_.y, light_direction_.z);
    glUniform3f(Location("light.ambient"), light_ambient_.x, light_ambient_.y, light_ambient_.z);
    glUniform3f(Location("light.diffuse"), light_diffuse_.x, light_diffuse_.y, light_diffuse_.z);
    glUniform3f(Location("light.specular"), light_specular_.x, light_specular_.y, light_specular_.z);
    glUniform1i(Location("material.diffuse"), material_diffuse_);
    glUniform1i(Location("material.specular"), material_specular_);
    glUniform1f(Location("material.shininess"), material_shininess_);
    glUniform3f(Location("viewPosition"), view_position_.x, view_position_.y, view_position_.z);
    OPENGL_DEBUG_CHECK();
}
