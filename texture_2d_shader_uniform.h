#ifndef SANDBOX_OPENGL_22_TEXTURE_2D_SHADER_UNIFORM_H_
#define SANDBOX_OPENGL_22_TEXTURE_2D_SHADER_UNIFORM_H_

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "shader_uniform.h"

class Texture2dShaderUniform : public ShaderUniform {
public:
    Texture2dShaderUniform(
            GLint uniform_texture_unit,
            GLint uniform_translation_vec,
            GLint uniform_scaling_vec,
            GLint uniform_texcoord_translation_vec,
            GLint uniform_texcoord_scaling_vec)
            : uniform_texture_unit_(uniform_texture_unit),
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

private:
    GLint texture_unit_{};
    glm::vec2 translation_{};
    glm::vec2 scaling_{};
    glm::vec2 texcoord_translation_{};
    glm::vec2 texcoord_scaling_{};

    GLint uniform_texture_unit_{-1};
    GLint uniform_translation_vec_{-1};
    GLint uniform_scaling_vec_{-1};
    GLint uniform_texcoord_translation_vec_{-1};
    GLint uniform_texcoord_scaling_vec_{-1};
};

#endif //SANDBOX_OPENGL_22_TEXTURE_2D_SHADER_UNIFORM_H_
