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

    [[nodiscard]] GLint GetPositionAttribVariableLocation() const {
        return position_attrib_variable_location_;
    }

    [[nodiscard]] GLint GetColorAttribVariableLocation() const {
        return color_attrib_variable_location_;
    }

    [[nodiscard]] GLint GetTexcoordAttribVariableLocation() const {
        return texcoord_attrib_variable_location_;
    }

    [[nodiscard]] GLint GetProjectionMatUniformLocation() const {
        return projection_mat_uniform_location_;
    }

    [[nodiscard]] GLint GetViewMatUniformLocation() const {
        return view_mat_uniform_location_;
    }

    [[nodiscard]] GLint GetModelMatUniformLocation() const {
        return model_mat_uniform_location_;
    }

    [[nodiscard]] GLint GetTextureUnitUniformLocation() const {
        return texture_unit_uniform_location_;
    }

    [[nodiscard]] GLint GetTranslationVecUniformLocation() const {
        return translation_vec_uniform_location_;
    }

    [[nodiscard]] GLint GetScalingVecUniformLocation() const {
        return scaling_vec_uniform_location_;
    }

    [[nodiscard]] GLint GetTexcoordTranslationVecUniformLocation() const {
        return texcoord_translation_vec_uniform_location_;
    }

    [[nodiscard]] GLint GetTexcoordScalingVecUniformLocation() const {
        return texcoord_scaling_vec_uniform_location_;
    }

    void Finalize() override;

private:
    static std::string LoadShaderSourceFromFile(const char *filepath);

    static GLuint BuildShader(GLenum shader_type, const GLchar *shader_source);

    GLuint program_object_{};
    GLuint vertex_shader_{};
    GLuint fragment_shader_{};

    // TODO shader によって変化する部分なので、それに対応できるような構造に変更したい
    // 'position' 属性変数の位置
    GLint position_attrib_variable_location_{};
    // 'color' 属性変数の位置
    GLint color_attrib_variable_location_{};
    // 'texcoord' 属性変数の位置
    GLint texcoord_attrib_variable_location_{};

    // TODO shader によって変化する部分なので、それに対応できるような構造に変更したい
    // uniform 変数の位置
    GLint projection_mat_uniform_location_{};
    GLint view_mat_uniform_location_{};
    GLint model_mat_uniform_location_{};
    GLint texture_unit_uniform_location_{};
    GLint translation_vec_uniform_location_{};
    GLint scaling_vec_uniform_location_{};
    GLint texcoord_translation_vec_uniform_location_{};
    GLint texcoord_scaling_vec_uniform_location_{};
};

#endif //SANDBOX_OPENGL_22_SHADER_H_
