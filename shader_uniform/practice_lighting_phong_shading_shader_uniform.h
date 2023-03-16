#ifndef SANDBOX_OPENGL_22_PRACTICE_LIGHTING_PHONG_SHADING_SHADER_UNIFORM_H_
#define SANDBOX_OPENGL_22_PRACTICE_LIGHTING_PHONG_SHADING_SHADER_UNIFORM_H_

#include <glm/glm.hpp>

#include "../opengl_glfw.h"
#include "shader_uniform.h"

class PracticeLightingPhongShadingShaderUniform : public ShaderUniform {
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

    void SetLightAmbient(const glm::vec3 &light_ambient) {
        light_ambient_ = light_ambient;
    }

    void SetLightDiffuse(const glm::vec3 &light_diffuse) {
        light_diffuse_ = light_diffuse;
    }

    void SetLightSpecular(const glm::vec3 &light_specular) {
        light_specular_ = light_specular;
    }

    void SetLightPosition(const glm::vec3 &light_position) {
        light_position_ = light_position;
    }

    void SetViewPosition(const glm::vec3 &view_position) {
        view_position_ = view_position;
    }

    void SetMaterialAmbient(const glm::vec3 &material_ambient) {
        material_ambient_ = material_ambient;
    }

    void SetMaterialDiffuse(const glm::vec3 &material_diffuse) {
        material_diffuse_ = material_diffuse;
    }

    void SetMaterialSpecular(const glm::vec3 &material_specular) {
        material_specular_ = material_specular;
    }

    void SetMaterialShininess(float material_shininess) {
        material_shininess_ = material_shininess;
    }

private:
    glm::mat4 projection_mat_{glm::mat4(1.f)};
    glm::mat4 view_mat_{glm::mat4(1.f)};
    glm::mat4 model_mat_{glm::mat4(1.f)};
    glm::vec3 light_position_{glm::vec3(0)};
    glm::vec3 light_ambient_{glm::vec3(0)};
    glm::vec3 light_diffuse_{glm::vec3(0)};
    glm::vec3 light_specular_{glm::vec3(0)};
    glm::vec3 view_position_{glm::vec3(0)};
    glm::vec3 material_ambient_{glm::vec3(0)};
    glm::vec3 material_diffuse_{glm::vec3(0)};
    glm::vec3 material_specular_{glm::vec3(0)};
    float material_shininess_{0};
};

#endif //SANDBOX_OPENGL_22_PRACTICE_LIGHTING_PHONG_SHADING_SHADER_UNIFORM_H_
