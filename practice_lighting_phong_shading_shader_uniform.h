#ifndef SANDBOX_OPENGL_22_PRACTICE_LIGHTING_PHONG_SHADING_SHADER_UNIFORM_H_
#define SANDBOX_OPENGL_22_PRACTICE_LIGHTING_PHONG_SHADING_SHADER_UNIFORM_H_

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "shader_uniform.h"

class PracticeLightingPhongShadingShaderUniform : public ShaderUniform {
public:
    PracticeLightingPhongShadingShaderUniform(
            GLint uniform_projection_mat,
            GLint uniform_view_mat,
            GLint uniform_model_mat,
            GLint uniform_light_position,
            GLint uniform_light_ambient,
            GLint uniform_light_diffuse,
            GLint uniform_light_specular,
            GLint uniform_view_position,
            GLint uniform_material_ambient,
            GLint uniform_material_diffuse,
            GLint uniform_material_specular,
            GLint uniform_material_shininess)
            : uniform_projection_mat_(uniform_projection_mat),
              uniform_view_mat_(uniform_view_mat),
              uniform_model_mat_(uniform_model_mat),
              uniform_light_position_(uniform_light_position),
              uniform_light_ambient_(uniform_light_ambient),
              uniform_light_diffuse_(uniform_light_diffuse),
              uniform_light_specular_(uniform_light_specular),
              uniform_view_position_(uniform_view_position),
              uniform_material_ambient_(uniform_material_ambient),
              uniform_material_diffuse_(uniform_material_diffuse),
              uniform_material_specular_(uniform_material_specular),
              uniform_material_shininess_(uniform_material_shininess) {}

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
    GLint uniform_projection_mat_{-1};
    GLint uniform_view_mat_{-1};
    GLint uniform_model_mat_{-1};
    GLint uniform_light_position_{-1};
    GLint uniform_light_ambient_{-1};
    GLint uniform_light_diffuse_{-1};
    GLint uniform_light_specular_{-1};
    GLint uniform_view_position_{-1};
    GLint uniform_material_ambient_{-1};
    GLint uniform_material_diffuse_{-1};
    GLint uniform_material_specular_{-1};
    GLint uniform_material_shininess_{-1};

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
