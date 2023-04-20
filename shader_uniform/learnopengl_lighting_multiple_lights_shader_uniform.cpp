#include <gl_app/debug_util.h>
#include <glm/gtc/type_ptr.hpp>

#include "learnopengl_lighting_multiple_lights_shader_uniform.h"

void LearnopenglLightingMultipleLightsShaderUniform::Transfer() const {
    glUniformMatrix4fv(Location("projection_mat"), 1, GL_FALSE, glm::value_ptr(projection_mat_));
    glUniformMatrix4fv(Location("view_mat"), 1, GL_FALSE, glm::value_ptr(view_mat_));
    glUniformMatrix4fv(Location("model_mat"), 1, GL_FALSE, glm::value_ptr(model_mat_));

    glUniform3f(Location("view_position"), view_position_.x, view_position_.y, view_position_.z);

    glUniform1i(Location("material.diffuse"), material_.diffuse);
    glUniform1i(Location("material.specular"), material_.specular);
    glUniform1f(Location("material.shininess"), material_.shininess);

    glUniform3fv(Location("directional_light.direction"), 1, glm::value_ptr(directional_light_.direction));
    glUniform3fv(Location("directional_light.ambient"), 1, glm::value_ptr(directional_light_.ambient));
    glUniform3fv(Location("directional_light.diffuse"), 1, glm::value_ptr(directional_light_.diffuse));
    glUniform3fv(Location("directional_light.specular"), 1, glm::value_ptr(directional_light_.specular));

    for (int i = 0; i < 4; i++) {
        glUniform3fv(Location(MakeName("point_lights", i, "position")), 1,
                     glm::value_ptr(point_light_[i].position));
        glUniform3fv(Location(MakeName("point_lights", i, "ambient")), 1,
                     glm::value_ptr(point_light_[i].ambient));
        glUniform3fv(Location(MakeName("point_lights", i, "diffuse")), 1,
                     glm::value_ptr(point_light_[i].diffuse));
        glUniform3fv(Location(MakeName("point_lights", i, "specular")), 1,
                     glm::value_ptr(point_light_[i].specular));

        glUniform1f(Location(MakeName("point_lights", i, "attenuation_constant")),
                    point_light_[i].attenuation_constant);
        glUniform1f(Location(MakeName("point_lights", i, "attenuation_linear")),
                    point_light_[i].attenuation_linear);
        glUniform1f(Location(MakeName("point_lights", i, "attenuation_quadratic")),
                    point_light_[i].attenuation_quadratic);
    }

    glUniform3fv(Location("spotlight.position"), 1, glm::value_ptr(spotlight_.position));
    glUniform3fv(Location("spotlight.direction"), 1, glm::value_ptr(spotlight_.direction));
    glUniform3fv(Location("spotlight.ambient"), 1, glm::value_ptr(spotlight_.ambient));
    glUniform3fv(Location("spotlight.diffuse"), 1, glm::value_ptr(spotlight_.diffuse));
    glUniform3fv(Location("spotlight.specular"), 1, glm::value_ptr(spotlight_.specular));
    glUniform1f(Location("spotlight.cutoff"), spotlight_.cutoff);
    glUniform1f(Location("spotlight.outer_cutoff"), spotlight_.outer_cutoff);
    glUniform1f(Location("spotlight.attenuation_constant"), spotlight_.attenuation_constant);
    glUniform1f(Location("spotlight.attenuation_linear"), spotlight_.attenuation_linear);
    glUniform1f(Location("spotlight.attenuation_quadratic"), spotlight_.attenuation_quadratic);
}

std::string LearnopenglLightingMultipleLightsShaderUniform::MakeName(const char *name, int index, const char *child) {
    // https://stackoverflow.com/a/900035
    return std::string(name) + std::string("[") + std::to_string(index) + std::string("].") + std::string(child);
}
