#ifndef SANDBOX_OPENGL_22_FONT_SHADER_UNIFORM_H_
#define SANDBOX_OPENGL_22_FONT_SHADER_UNIFORM_H_

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "shader_uniform.h"

class FontShaderUniform : public ShaderUniform {
public:
    FontShaderUniform(
            GLint uniform_texture_unit,
            GLint uniform_color,
            GLint uniform_translation_vec,
            GLint uniform_scaling_vec,
            GLint uniform_texcoord_translation_vec,
            GLint uniform_texcoord_scaling_vec)
            : uniform_texture_unit_(uniform_texture_unit),
              uniform_color_(uniform_color),
              uniform_translation_vec_(uniform_translation_vec),
              uniform_scaling_vec_(uniform_scaling_vec),
              uniform_texcoord_translation_vec_(uniform_texcoord_translation_vec),
              uniform_texcoord_scaling_vec_(uniform_texcoord_scaling_vec) { Activate(); }

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

    GLint uniform_texture_unit_{-1};
    GLint uniform_color_{-1};
    GLint uniform_translation_vec_{-1};
    GLint uniform_scaling_vec_{-1};
    GLint uniform_texcoord_translation_vec_{-1};
    GLint uniform_texcoord_scaling_vec_{-1};
};

#endif //SANDBOX_OPENGL_22_FONT_SHADER_UNIFORM_H_
