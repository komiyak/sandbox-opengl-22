#ifndef SANDBOX_OPENGL_22_SHADER_H_
#define SANDBOX_OPENGL_22_SHADER_H_

#include <glad/glad.h>
#include <string>

#include "base_object.h"

class Shader : public BaseObject {
public:
    // glUseProgram() を発行
    void UseProgram() const;

    // shader file をビルドし、shader を利用可能にする
    void BuildFromFile(const char *vertex_shader_filepath, const char *fragment_shader_filepath);

    [[nodiscard]] GLint GetPositionAttribLocation() const {
        return position_attrib_location_;
    }

    [[nodiscard]] GLint GetColorAttribLocation() const {
        return color_attrib_location_;
    }

    [[nodiscard]] GLint GetTexcoordAttribLocation() const {
        return texcoord_attrib_location_;
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

    [[nodiscard]] GLint GetUniformLocationOfTextureUnit() const {
        return uniform_texture_unit_;
    }

    void Finalize() override;

private:
    static std::string LoadShaderSourceFromFile(const char *filepath);

    static GLuint BuildShader(GLenum shader_type, const GLchar *shader_source);

    GLuint program_object_{};
    GLuint vertex_shader_{};
    GLuint fragment_shader_{};

    // 'position' 属性変数の位置
    GLint position_attrib_location_{};
    // 'color' 属性変数の位置
    GLint color_attrib_location_{};
    // 'texcoord' 属性変数の位置
    GLint texcoord_attrib_location_{};

    // TODO shader によって変化する部分なので、それに対応できるような構造に変更する
    GLint uniform_projection_mat_{};
    GLint uniform_view_mat_{};
    GLint uniform_model_mat_{};
    GLint uniform_texture_unit_{};
};

#endif //SANDBOX_OPENGL_22_SHADER_H_
