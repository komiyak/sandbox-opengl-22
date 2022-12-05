#ifndef SANDBOX_OPENGL_22_SAMPLE_LIGHTING_CUBE_SHADER_UNIFORM_H_
#define SANDBOX_OPENGL_22_SAMPLE_LIGHTING_CUBE_SHADER_UNIFORM_H_

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "shader_uniform.h"

class SampleLightingCubeShaderUniform : public ShaderUniform {
public:
    SampleLightingCubeShaderUniform(
            GLint uniform_projection_mat,
            GLint uniform_view_mat,
            GLint uniform_model_mat,
            GLint uniform_object_color,
            GLint uniform_light_color) :
            uniform_projection_mat_(uniform_projection_mat),
            uniform_view_mat_(uniform_view_mat),
            uniform_model_mat_(uniform_model_mat),
            uniform_object_color_(uniform_object_color),
            uniform_light_color_(uniform_light_color) {}

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

    void SetObjectColor(const glm::vec3 &object_color) {
        object_color_ = object_color;
    }

    void SetLightColor(const glm::vec3 &light_color) {
        light_color_ = light_color;
    }

private:
    GLint uniform_projection_mat_{-1};
    GLint uniform_view_mat_{-1};
    GLint uniform_model_mat_{-1};
    GLint uniform_object_color_{-1};
    GLint uniform_light_color_{-1};

    glm::mat4 projection_mat_{glm::mat4(1.f)};
    glm::mat4 view_mat_{glm::mat4(1.f)};
    glm::mat4 model_mat_{glm::mat4(1.f)};
    glm::vec3 object_color_{glm::vec3(1)};
    glm::vec3 light_color_{glm::vec3(1)};
};


#endif //SANDBOX_OPENGL_22_SAMPLE_LIGHTING_CUBE_SHADER_UNIFORM_H_
