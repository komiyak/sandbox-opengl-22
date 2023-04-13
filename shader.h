#ifndef SANDBOX_OPENGL_22_SHADER_H_
#define SANDBOX_OPENGL_22_SHADER_H_

#include <string>
#include <gl_app/gl.h>

class Shader {
public:
    Shader() = default;

    ~Shader();

    Shader(const Shader &) = delete;

    Shader &operator=(const Shader &) = delete;

    // shader file をビルドし、shader を利用可能にする
    // param vertex_shader_filepath Vertex shader ファイル
    // param fragment_shader_filepath Fragment shader ファイル
    // param fragment_data_location_name glBindFragDataLocation で指定する変数名
    void BuildFromFile(
            const std::string &vertex_shader_filepath,
            const std::string &fragment_shader_filepath,
            const std::string &fragment_data_location_name);

    // 利用中の shader を破壊する
    void Destroy();

    // glUseProgram() を発行
    void UseProgram() const;

    // Get the location of attribute variable in the shader.
    [[maybe_unused]] [[nodiscard]] GLint GetAttribVariableLocation(const std::string &name) const;

    // Get the location of uniform variable in the shader.
    [[maybe_unused]] [[nodiscard]] GLint GetUniformVariableLocation(const std::string &name) const;

private:
    // 任意のシェーダーファイルを読み取る
    static std::string LoadShaderSourceFromFile(const std::string &filepath);

    static GLuint BuildShader(GLenum shader_type, const std::string &shader_source);

    // glUniformLocation() を実行
    static GLint GetUniformVariableLocationFromProgramObject(
            GLuint program_object,
            const std::string &name,
            const std::string &vertex_shader_filepath,
            const std::string &fragment_shader_filepath);

    // glAttribLocation() を実行
    static GLint GetAttribVariableLocationFromProgramObject(
            GLuint program_object,
            const std::string &name,
            const std::string &vertex_shader_filepath,
            const std::string &fragment_shader_filepath);

    // シェーダーを構築済みならば true
    bool built_{};

    GLuint program_object_{};
    GLuint vertex_shader_{};
    GLuint fragment_shader_{};

    std::string vertex_shader_filepath_{};
    std::string fragment_shader_filepath_{};
};

#endif //SANDBOX_OPENGL_22_SHADER_H_
