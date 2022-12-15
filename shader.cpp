#include <fstream>
#include <sstream>

#include "shader.h"
#include "opengl_debug.h"
#include "debug.h"
#include "cstring_util.h"

std::string Shader::LoadShaderSourceFromFile(const char *filepath) {
    std::ifstream input_file_stream;
    input_file_stream.open(filepath);
    std::stringstream string_stream;
    string_stream << input_file_stream.rdbuf();
    return string_stream.str();
}

void Shader::BuildFromFile(
        const char *vertex_shader_filepath,
        const char *fragment_shader_filepath) {

    DEBUG_ASSERT_MESSAGE(
            cstring_util::EqualLast(vertex_shader_filepath, ".vert"),
            "Vertex shader file must be with '.vert' extension.");
    DEBUG_ASSERT_MESSAGE(
            cstring_util::EqualLast(fragment_shader_filepath, ".frag"),
            "Vertex shader file must be with '.frag' extension.");

    prepared_ = true;
    p_vertex_shader_filepath_ = vertex_shader_filepath;
    p_fragment_shader_filepath_ = fragment_shader_filepath;


    const std::string vertex_shader_source = LoadShaderSourceFromFile(p_vertex_shader_filepath_);
    const std::string fragment_shader_source = LoadShaderSourceFromFile(p_fragment_shader_filepath_);

    vertex_shader_ = BuildShader(GL_VERTEX_SHADER, vertex_shader_source.c_str());
    fragment_shader_ = BuildShader(GL_FRAGMENT_SHADER, fragment_shader_source.c_str());


    program_object_ = glCreateProgram();
    glAttachShader(program_object_, vertex_shader_);
    glAttachShader(program_object_, fragment_shader_);
    glBindFragDataLocation(program_object_, 0, "outColor"); // outColor に色を出力する
    glLinkProgram(program_object_);
    OPENGL_DEBUG_CHECK();
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"

GLuint Shader::BuildShader(GLenum shader_type, const GLchar *shader_source) {
    GLuint result = glCreateShader(shader_type);
    glShaderSource(result, 1, &shader_source, nullptr);
    glCompileShader(result);
    OPENGL_DEBUG_CHECK();

    GLint status;
    glGetShaderiv(result, GL_COMPILE_STATUS, &status);
    OPENGL_DEBUG_CHECK();
    if (!status) {
        const char *shader_type_name;

        switch (shader_type) {
            case GL_VERTEX_SHADER:
                shader_type_name = "GL_VERTEX_SHADER(0x8B31)";
                break;
            case GL_FRAGMENT_SHADER:
                shader_type_name = "GL_FRAGMENT_SHADER(0x8B30)";
                break;
            default:
                shader_type_name = "unknown";
        }

        fprintf(stderr, "Shader compile error [%s].\n", shader_type_name);
        char buffer[512];
        glGetShaderInfoLog(result, 512, nullptr, buffer);
        fprintf(stderr, "%s\n", buffer);
        fflush(stderr);
    }

    return result;
}

#pragma clang diagnostic pop

void Shader::Finalize() {
    if (prepared_) {
        glDeleteProgram(program_object_);
        glDeleteShader(vertex_shader_); // Note: program_object を生成した段階で、これは delete してよいらしい
        glDeleteShader(fragment_shader_); // Note: program_object を生成した段階で、これは delete してよいらしい
        program_object_ = 0;
        vertex_shader_ = 0;
        fragment_shader_ = 0;
    }
    prepared_ = false;
}

void Shader::UseProgram() const {
    if (!prepared_) return;

    glUseProgram(program_object_);
    OPENGL_DEBUG_CHECK();
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"

GLint Shader::GetUniformVariableLocationFromProgramObject(
        GLuint program_object,
        const char *name,
        const char *vertex_shader_filepath,
        const char *fragment_shader_filepath) {

    const GLint location = glGetUniformLocation(program_object, name);
    OPENGL_DEBUG_CHECK();

    if (kRuntimeAssertion && location == -1) {
        fprintf(stderr, "The uniform variable location '%s' is not found in '%s' or '%s'.\n",
                name,
                vertex_shader_filepath,
                fragment_shader_filepath);
        abort();
    }
    return location;
}

#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"

GLint Shader::GetAttribVariableLocationFromProgramObject(
        GLuint program_object,
        const char *name,
        const char *vertex_shader_filepath,
        const char *fragment_shader_filepath) {

    const GLint location = glGetAttribLocation(program_object, name);
    OPENGL_DEBUG_CHECK();

    if (kRuntimeAssertion && location == -1) {
        fprintf(stderr, "The attribute variable location '%s' is not found in '%s' or '%s'.\n",
                name,
                vertex_shader_filepath,
                fragment_shader_filepath);
        abort();
    }
    return location;
}

GLint Shader::GetAttribVariableLocation(const char *name) {
    if (!prepared_) return -1;

    // Note: もし最適化が必要になった場合は、一度取得した値をキャッシュする
    return GetAttribVariableLocationFromProgramObject(
            program_object_, name, p_vertex_shader_filepath_, p_fragment_shader_filepath_);
}

GLint Shader::GetUniformVariableLocation(const char *name) {
    if (!prepared_) return -1;

    // Note: もし最適化が必要になった場合は、一度取得した値をキャッシュする
    return GetUniformVariableLocationFromProgramObject(
            program_object_, name, p_vertex_shader_filepath_, p_fragment_shader_filepath_);
}

#pragma clang diagnostic pop
