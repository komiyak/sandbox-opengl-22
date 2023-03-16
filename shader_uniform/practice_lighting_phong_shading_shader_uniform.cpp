#include <glm/gtc/type_ptr.hpp>

#include "practice_lighting_phong_shading_shader_uniform.h"
#include "../opengl_debug.h"

void PracticeLightingPhongShadingShaderUniform::Transfer() const {
    glUniformMatrix4fv(Location("projection_mat"), 1, GL_FALSE, glm::value_ptr(projection_mat_));
    glUniformMatrix4fv(Location("view_mat"), 1, GL_FALSE, glm::value_ptr(view_mat_));
    glUniformMatrix4fv(Location("model_mat"), 1, GL_FALSE, glm::value_ptr(model_mat_));
    glUniform3f(Location("light.position"), light_position_.x, light_position_.y, light_position_.z);
    glUniform3f(Location("light.ambient"), light_ambient_.x, light_ambient_.y, light_ambient_.z);
    glUniform3f(Location("light.diffuse"), light_diffuse_.x, light_diffuse_.y, light_diffuse_.z);
    glUniform3f(Location("light.specular"), light_specular_.x, light_specular_.y, light_specular_.z);
    glUniform3f(Location("viewPosition"), view_position_.x, view_position_.y, view_position_.z);
    glUniform3f(Location("material.ambient"), material_ambient_.x, material_ambient_.y, material_ambient_.z);
    glUniform3f(Location("material.diffuse"), material_diffuse_.x, material_diffuse_.y, material_diffuse_.z);
    glUniform3f(Location("material.specular"), material_specular_.x, material_specular_.y, material_specular_.z);
    glUniform1f(Location("material.shininess"), material_shininess_);
    OPENGL_DEBUG_CHECK();
}
