#ifndef SANDBOX_OPENGL_22_SHADER_H_
#define SANDBOX_OPENGL_22_SHADER_H_

#include <glad/glad.h>
#include <map>
#include <string>

#include "base_object.h"

class Shader : public BaseObject {
public:
    // glUseProgram() を発行
    void UseProgram() const;

    // shader file をビルドし、shader を利用可能にする
    // param vertex_shader_filepath Vertex shader ファイル
    // param fragment_shader_filepath Fragment shader ファイル
    // param attrib_variable_location_names Shader 内に定義されている属性変数の名前リスト
    // param attrib_variable_location_names_size attrib_variable_location_names's size
    // param uniform_variable_location_names Shader 内に定義されている uniform 変数の名前リスト
    // param uniform_variable_location_names_size uniform_variable_location_names's size
    void BuildFromFile(
            const char *vertex_shader_filepath,
            const char *fragment_shader_filepath,
            const char *const *attrib_variable_location_names,
            std::size_t attrib_variable_location_names_size,
            const char *const *uniform_variable_location_names,
            std::size_t uniform_variable_location_names_size);

    void Finalize() override;

    [[maybe_unused]] GLint GetAttribVariableLocation(const char *name) {
        return attrib_variable_locations_.at(name);
    }

    [[maybe_unused]] GLint GetUniformVariableLocation(const char *name) {
        return uniform_variable_locations_.at(name);
    }

private:
    static std::string LoadShaderSourceFromFile(const char *filepath);

    static GLuint BuildShader(GLenum shader_type, const GLchar *shader_source);

    GLuint program_object_{};
    GLuint vertex_shader_{};
    GLuint fragment_shader_{};

    // 属性変数の位置
    std::map<std::string, GLint> attrib_variable_locations_{};
    // uniform 変数の位置
    std::map<std::string, GLint> uniform_variable_locations_{};
};

#endif //SANDBOX_OPENGL_22_SHADER_H_
