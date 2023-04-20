#ifndef SANDBOX_OPENGL_22_FONT_SHADER_UNIFORM_H_
#define SANDBOX_OPENGL_22_FONT_SHADER_UNIFORM_H_

#include <glm/glm.hpp>

#include <gl_app/gl.h>
#include "shader_uniform.h"

class FontShaderUniform : public ShaderUniform {
public:
    void Transfer() const override;

    void SetTextureUnit(GLint texture_unit) {
        texture_unit_ = texture_unit;
    }

    void SetTranslation(const glm::vec2 &translation) {
        translation_ = translation;
    }

    void SetScaling(const glm::vec2 &scaling) {
        scaling_ = scaling;
    }

    void SetTexcoordTranslation(const glm::vec2 &texcoord_translation) {
        texcoord_translation_ = texcoord_translation;
    }

    void SetTexcoordScaling(const glm::vec2 &texcoord_scaling) {
        texcoord_scaling_ = texcoord_scaling;
    }

    void SetColor(const glm::vec3 &color) {
        color_ = color;
    }

private:
    GLint texture_unit_{};
    glm::vec2 translation_{};
    glm::vec2 scaling_{};
    glm::vec2 texcoord_translation_{};
    glm::vec2 texcoord_scaling_{};
    glm::vec3 color_{};
};

#endif //SANDBOX_OPENGL_22_FONT_SHADER_UNIFORM_H_
