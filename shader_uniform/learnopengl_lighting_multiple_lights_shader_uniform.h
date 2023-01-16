#ifndef SANDBOX_OPENGL_22_LEARNOPENGL_LIGHTING_MULTIPLE_LIGHTS_H_
#define SANDBOX_OPENGL_22_LEARNOPENGL_LIGHTING_MULTIPLE_LIGHTS_H_

#include <glm/glm.hpp>

#include "../opengl_glfw.h"
#include "shader_uniform.h"
#include "../shader.h"

class LearnopenglLightingMultipleLightsShaderUniform : public ShaderUniform {
public:
    struct Material {
        GLint diffuse;
        GLint specular;
        float shininess;
    };

    struct DirectionalLight {
        glm::vec3 direction;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    };

    struct PointLight {
        glm::vec3 position;

        float attenuation_constant;
        float attenuation_linear;
        float attenuation_quadratic;

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    };

    struct Spotlight {
        glm::vec3 position;
        glm::vec3 direction;
        float cutoff;
        float outer_cutoff;

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;

        float attenuation_constant;
        float attenuation_linear;
        float attenuation_quadratic;
    };

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

    void SetViewPosition(const glm::vec3 &view_position) {
        view_position_ = view_position;
    }

    void SetMaterial(const Material &material) {
        material_ = material;
    }

    void SetDirectionalLight(const DirectionalLight &directional_light) {
        directional_light_ = directional_light;
    }

    void SetSpotlight(const Spotlight &spotlight) {
        spotlight_ = spotlight;
    }

    void SetPointLight(const PointLight &point_light, int index) {
        point_light_[index] = point_light;
    }

private:
    static std::string MakeName(const char *name, int index, const char *child);

    glm::mat4 projection_mat_{glm::mat4(1.f)};
    glm::mat4 view_mat_{glm::mat4(1.f)};
    glm::mat4 model_mat_{glm::mat4(1.f)};

    glm::vec3 view_position_{glm::vec3(0)};

    Material material_;
    DirectionalLight directional_light_;
    PointLight point_light_[4];
    Spotlight spotlight_;
};

#endif //SANDBOX_OPENGL_22_LEARNOPENGL_LIGHTING_MULTIPLE_LIGHTS_H_
