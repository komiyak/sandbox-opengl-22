#include <glm/gtc/type_ptr.hpp>

#include "learnopengl_lighting_directional_light_shader_uniform.h"
#include "opengl_debug.h"

void LearnopenglLightingDirectionalLightShaderUniform::Transfer() const {
    if (!activated_) return;

    glUniformMatrix4fv(uniform_projection_mat_, 1, GL_FALSE, glm::value_ptr(projection_mat_));
    glUniformMatrix4fv(uniform_view_mat_, 1, GL_FALSE, glm::value_ptr(view_mat_));
    glUniformMatrix4fv(uniform_model_mat_, 1, GL_FALSE, glm::value_ptr(model_mat_));
    glUniform3f(uniform_light_ambient_, light_ambient_.x, light_ambient_.y, light_ambient_.z);
    glUniform3f(uniform_light_diffuse_, light_diffuse_.x, light_diffuse_.y, light_diffuse_.z);
    glUniform3f(uniform_light_specular_, light_specular_.x, light_specular_.y, light_specular_.z);
    glUniform1i(uniform_material_diffuse_, material_diffuse_);
    glUniform1i(uniform_material_specular_, material_specular_);
    glUniform1f(uniform_material_shininess_, material_shininess_);
    glUniform3f(uniform_view_position_, view_position_.x, view_position_.y, view_position_.z);
    OPENGL_DEBUG_CHECK();
}
