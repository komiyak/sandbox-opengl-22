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
    void BuildFromFile(
            const char *vertex_shader_filepath,
            const char *fragment_shader_filepath);

    void Finalize() override;

    [[maybe_unused]] GLint GetAttribVariableLocation(const char *name);

    [[maybe_unused]] GLint GetUniformVariableLocation(const char *name);

private:
    static std::string LoadShaderSourceFromFile(const char *filepath);

    static GLuint BuildShader(GLenum shader_type, const GLchar *shader_source);

    static GLint GetUniformVariableLocationFromProgramObject(
            GLuint program_object,
            const char *name,
            const char *vertex_shader_filepath,
            const char *fragment_shader_filepath);

    static GLint GetAttribVariableLocationFromProgramObject(
            GLuint program_object,
            const char *name,
            const char *vertex_shader_filepath,
            const char *fragment_shader_filepath);

    GLuint program_object_{};
    GLuint vertex_shader_{};
    GLuint fragment_shader_{};

    const char *vertex_shader_filepath_{};
    const char *fragment_shader_filepath_{};
};

#endif //SANDBOX_OPENGL_22_SHADER_H_
