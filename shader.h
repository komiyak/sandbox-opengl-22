//
// Created by komiyak on 22/11/21.
//

#ifndef SANDBOX_OPENGL_22_SHADER_H_
#define SANDBOX_OPENGL_22_SHADER_H_

#include <glad/glad.h>
#include <string>
#include "base_object.h"

class Shader : public BaseObject {
public:
    void Use() const;

    void LoadFromFile(const char *vertex_shader_filepath, const char *fragment_shader_filepath);

    [[nodiscard]] GLint GetPositionAttribLocation() const {
        return glGetAttribLocation(program_object_, "position");
    }

    [[nodiscard]] GLint GetUniformLocationOfProjectionMatrix() const {
        return uniform_projection_matrix_;
    }

    [[nodiscard]] GLint GetUniformLocationOfViewMatrix() const {
        return uniform_view_matrix_;
    }

    [[nodiscard]] GLint GetUniformLocationOfModelMatrix() const {
        return uniform_model_matrix_;
    }

    void Finalize() override;

private:
    static std::string LoadShaderSourceFromFile(const char *filepath);

    static GLuint BuildShader(GLenum shader_type, const GLchar *shader_source);

    GLuint program_object_{};
    GLuint vertex_shader_{};
    GLuint fragment_shader_{};

    // TODO shader によって変化する部分なので、それに対応できるような構造に変更する
    GLint uniform_projection_matrix_{};
    GLint uniform_view_matrix_{};
    GLint uniform_model_matrix_{};
};

#endif //SANDBOX_OPENGL_22_SHADER_H_
