#ifndef SANDBOX_OPENGL_22_BASIC_SHADER_UNIFORM_H_
#define SANDBOX_OPENGL_22_BASIC_SHADER_UNIFORM_H_

#include <glm/glm.hpp>

#include <gl_app/gl.h>
#include "shader_uniform.h"

class BasicShaderUniform : public ShaderUniform {
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

private:
    glm::mat4 projection_mat_{glm::mat4(1.f)};
    glm::mat4 view_mat_{glm::mat4(1.f)};
    glm::mat4 model_mat_{glm::mat4(1.f)};
};

#endif //SANDBOX_OPENGL_22_BASIC_SHADER_UNIFORM_H_
