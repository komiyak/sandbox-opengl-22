#ifndef SANDBOX_OPENGL_22_LEARNOPENGL_LIGHTING_SPOTLIGHT_SHADER_UNIFORM_H_
#define SANDBOX_OPENGL_22_LEARNOPENGL_LIGHTING_SPOTLIGHT_SHADER_UNIFORM_H_

#include <glm/glm.hpp>

#include "../opengl_glfw.h"
#include "shader_uniform.h"

class LearnopenglLightingSpotlightShaderUniform : public ShaderUniform {
public:
    void SetUniformLocations(
            GLint uniform_projection_mat,
            GLint uniform_view_mat,
            GLint uniform_model_mat,
            GLint uniform_light_position,
            GLint uniform_light_direction,
            GLint uniform_light_cutoff,
            GLint uniform_light_outer_cutoff,
            GLint uniform_light_ambient,
            GLint uniform_light_diffuse,
            GLint uniform_light_specular,
            GLint uniform_light_constant,
            GLint uniform_light_linear,
            GLint uniform_light_quadratic,
            GLint uniform_material_diffuse,
            GLint uniform_material_specular,
            GLint uniform_material_shininess,
            GLint uniform_view_position) {
        uniform_projection_mat_ = uniform_projection_mat;
        uniform_view_mat_ = uniform_view_mat;
        uniform_model_mat_ = uniform_model_mat;
        uniform_light_position_ = uniform_light_position;
        uniform_light_direction_ = uniform_light_direction;
        uniform_light_cutoff_ = uniform_light_cutoff;
        uniform_light_outer_cutoff_ = uniform_light_outer_cutoff;
        uniform_light_ambient_ = uniform_light_ambient;
        uniform_light_diffuse_ = uniform_light_diffuse;
        uniform_light_specular_ = uniform_light_specular;
        uniform_light_constant_ = uniform_light_constant;
        uniform_light_linear_ = uniform_light_linear;
        uniform_light_quadratic_ = uniform_light_quadratic;
        uniform_material_diffuse_ = uniform_material_diffuse;
        uniform_material_specular_ = uniform_material_specular;
        uniform_material_shininess_ = uniform_material_shininess;
        uniform_view_position_ = uniform_view_position;
        Activate();
    }

    void Transfer() const override;

    void SetProjectionMat(const glm::mat4 &projection_mat) {
        projection_mat_ = projection_mat;
    }

    void SetViewMat(const glm::mat4 &view_mat) {
        view_mat_ = view_mat;
    }

    void SetModelMat(const glm::mat4 &model_mat) {
        model_mat_ = model_mat;
    }

    void SetLightPosition(const glm::vec3 &light_position) {
        light_position_ = light_position;
    }

    void SetLightDirection(const glm::vec3 &light_direction) {
        light_direction_ = light_direction;
    }

    void SetLightCutoff(GLfloat light_cutoff) {
        light_cutoff_ = light_cutoff;
    }

    void SetLightOuterCutoff(GLfloat light_outer_cutoff) {
        light_outer_cutoff_ = light_outer_cutoff;
    }

    void SetLightAmbient(const glm::vec3 &light_ambient) {
        light_ambient_ = light_ambient;
    }

    void SetLightDiffuse(const glm::vec3 &light_diffuse) {
        light_diffuse_ = light_diffuse;
    }

    void SetLightSpecular(const glm::vec3 &light_specular) {
        light_specular_ = light_specular;
    }

    void SetMaterialDiffuse(GLint material_diffuse) {
        material_diffuse_ = material_diffuse;
    }

    void SetMaterialSpecular(GLint material_specular) {
        material_specular_ = material_specular;
    }

    void SetMaterialShininess(GLfloat material_shininess) {
        material_shininess_ = material_shininess;
    }

    void SetViewPosition(const glm::vec3 &view_position) {
        view_position_ = view_position;
    }

    void SetLightConstant(GLfloat light_constant) {
        light_constant_ = light_constant;
    }

    void SetLightLinear(GLfloat light_linear) {
        light_linear_ = light_linear;
    }

    void SetLightQuadratic(GLfloat light_quadratic) {
        light_quadratic_ = light_quadratic;
    }

private:
    GLint uniform_projection_mat_{-1};
    GLint uniform_view_mat_{-1};
    GLint uniform_model_mat_{-1};
    GLint uniform_light_position_{-1};
    GLint uniform_light_direction_{-1};
    GLint uniform_light_cutoff_{-1};
    GLint uniform_light_outer_cutoff_{-1};
    GLint uniform_light_ambient_{-1};
    GLint uniform_light_diffuse_{-1};
    GLint uniform_light_specular_{-1};
    GLint uniform_light_constant_{-1};
    GLint uniform_light_linear_{-1};
    GLint uniform_light_quadratic_{-1};
    GLint uniform_material_diffuse_{-1};
    GLint uniform_material_specular_{-1};
    GLint uniform_material_shininess_{-1};
    GLint uniform_view_position_{-1};

    glm::mat4 projection_mat_{glm::mat4(1.f)};
    glm::mat4 view_mat_{glm::mat4(1.f)};
    glm::mat4 model_mat_{glm::mat4(1.f)};
    glm::vec3 light_position_{glm::vec3(0)};
    glm::vec3 light_direction_{glm::vec3(0)};
    GLfloat light_cutoff_{};
    GLfloat light_outer_cutoff_{};
    glm::vec3 light_ambient_{glm::vec3(0)};
    glm::vec3 light_diffuse_{glm::vec3(0)};
    glm::vec3 light_specular_{glm::vec3(0)};
    GLfloat light_constant_{};
    GLfloat light_linear_{};
    GLfloat light_quadratic_{};
    GLint material_diffuse_{};
    GLint material_specular_{};
    GLfloat material_shininess_{};
    glm::vec3 view_position_{glm::vec3(0)};
};

#endif //SANDBOX_OPENGL_22_LEARNOPENGL_LIGHTING_SPOTLIGHT_SHADER_UNIFORM_H_
