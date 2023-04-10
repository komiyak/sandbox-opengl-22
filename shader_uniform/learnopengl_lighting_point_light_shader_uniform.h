#ifndef SANDBOX_OPENGL_22_LEARNOPENGL_LIGHTING_POINT_LIGHT_SHADER_UNIFORM_H_
#define SANDBOX_OPENGL_22_LEARNOPENGL_LIGHTING_POINT_LIGHT_SHADER_UNIFORM_H_

#include <glm/glm.hpp>

#include "../opengl_glfw.h"
#include "shader_uniform.h"

class LearnopenglLightingPointLightShaderUniform : public ShaderUniform {
public:
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

    void SetLightAmbient(const glm::vec3 &light_ambient) {
        light_ambient_ = light_ambient;
    }

    void SetLightDiffuse(const glm::vec3 &light_diffuse) {
        light_diffuse_ = light_diffuse;
    }

    void SetLightSpecular(const glm::vec3 &light_specular) {
        light_specular_ = light_specular;
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

    void SetMaterialDiffuse(GLint material_diffuse) {
        material_diffuse_ = material_diffuse;
    }

    void SetMaterialSpecular(GLint material_specular) {
        material_specular_ = material_specular;
    }

    void SetMaterialShininess(float material_shininess) {
        material_shininess_ = material_shininess;
    }

    void SetViewPosition(const glm::vec3 &view_position) {
        view_position_ = view_position;
    }

private:
    glm::mat4 projection_mat_{glm::mat4(1.f)};
    glm::mat4 view_mat_{glm::mat4(1.f)};
    glm::mat4 model_mat_{glm::mat4(1.f)};
    glm::vec3 light_position_{glm::vec3(0)};
    glm::vec3 light_ambient_{glm::vec3(0)};
    glm::vec3 light_diffuse_{glm::vec3(0)};
    glm::vec3 light_specular_{glm::vec3(0)};
    GLfloat light_constant_{};
    GLfloat light_linear_{};
    GLfloat light_quadratic_{};
    GLint material_diffuse_{};
    GLint material_specular_{};
    float material_shininess_{};
    glm::vec3 view_position_{glm::vec3(0)};
};

#endif //SANDBOX_OPENGL_22_LEARNOPENGL_LIGHTING_POINT_LIGHT_SHADER_UNIFORM_H_
