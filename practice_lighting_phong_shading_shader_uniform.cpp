#include <glm/gtc/type_ptr.hpp>

#include "practice_lighting_phong_shading_shader_uniform.h"
#include "opengl_debug.h"

void PracticeLightingPhongShadingShaderUniform::Transfer() const {
    glUniformMatrix4fv(uniform_projection_mat_, 1, GL_FALSE, glm::value_ptr(projection_mat_));
    glUniformMatrix4fv(uniform_view_mat_, 1, GL_FALSE, glm::value_ptr(view_mat_));
    glUniformMatrix4fv(uniform_model_mat_, 1, GL_FALSE, glm::value_ptr(model_mat_));
    glUniform3f(uniform_object_color_, object_color_.x, object_color_.y, object_color_.z);
    glUniform3f(uniform_light_color_, light_color_.x, light_color_.y, light_color_.z);
    glUniform3f(uniform_light_position_, light_position_.x, light_position_.y, light_position_.z);
    glUniform3f(uniform_view_position_, view_position_.x, view_position_.y, view_position_.z);
    glUniform3f(uniform_material_ambient_, material_ambient_.x, material_ambient_.y, material_ambient_.z);
    glUniform3f(uniform_material_diffuse_, material_diffuse_.x, material_diffuse_.y, material_diffuse_.z);
    glUniform3f(uniform_material_specular_, material_specular_.x, material_specular_.y, material_specular_.z);
    glUniform1f(uniform_material_shininess_, material_shininess_);
    OPENGL_DEBUG_CHECK();
}