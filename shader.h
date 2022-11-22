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

    [[nodiscard]] GLint GetUniformLocationOfProjectionMat() const {
        return uniform_projection_mat_;
    }

    [[nodiscard]] GLint GetUniformLocationOfViewMat() const {
        return uniform_view_mat_;
    }

    [[nodiscard]] GLint GetUniformLocationOfModelMat() const {
        return uniform_model_mat_;
    }

    void Finalize() override;

private:
    static std::string LoadShaderSourceFromFile(const char *filepath);

    static GLuint BuildShader(GLenum shader_type, const GLchar *shader_source);

    GLuint program_object_{};
    GLuint vertex_shader_{};
    GLuint fragment_shader_{};

    // TODO shader によって変化する部分なので、それに対応できるような構造に変更する
    GLint uniform_projection_mat_{};
    GLint uniform_view_mat_{};
    GLint uniform_model_mat_{};
};

#endif //SANDBOX_OPENGL_22_SHADER_H_
