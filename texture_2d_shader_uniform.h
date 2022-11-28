#ifndef SANDBOX_OPENGL_22_TEXTURE_2D_SHADER_UNIFORM_H_
#define SANDBOX_OPENGL_22_TEXTURE_2D_SHADER_UNIFORM_H_


#include <glad/glad.h>
#include <glm/glm.hpp>

#include "shader_uniform.h"

class Texture2dShaderUniform : public ShaderUniform {
public:
    Texture2dShaderUniform(GLint uniform_texture_unit) : uniform_texture_unit_(uniform_texture_unit) {}

    void Transfer() const override;

    void SetTextureUnit(GLint texture_unit) {
        texture_unit_ = texture_unit;
    }

private:
    GLint texture_unit_{};

    GLint uniform_texture_unit_{-1};
};


#endif //SANDBOX_OPENGL_22_TEXTURE_2D_SHADER_UNIFORM_H_
