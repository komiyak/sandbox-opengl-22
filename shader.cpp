#include <fstream>
#include <sstream>
#include <iostream>

#include "shader.h"
#include "opengl_debug.h"
#include "debug.h"
#include "cstring_util.h"

std::string Shader::LoadShaderSourceFromFile(const std::string& filepath) {
    std::ifstream input_file_stream;
    input_file_stream.open(filepath);
    std::stringstream string_stream;
    string_stream << input_file_stream.rdbuf();
    return string_stream.str();
}

void Shader::BuildFromFile(
        const std::string& vertex_shader_filepath,
        const std::string& fragment_shader_filepath,
        const std::string& fragment_data_location_name) {

    // FIXME: std::string style の文字列比較に変更する
    DEBUG_ASSERT_MESSAGE(
            cstring_util::EqualLast(vertex_shader_filepath.c_str(), ".vert"),
            "Vertex shader file must be with '.vert' extension.");
    DEBUG_ASSERT_MESSAGE(
            cstring_util::EqualLast(fragment_shader_filepath.c_str(), ".frag"),
            "Vertex shader file must be with '.frag' extension.");

    vertex_shader_filepath_ = vertex_shader_filepath;
    fragment_shader_filepath_ = fragment_shader_filepath;


    const std::string vertex_shader_source = LoadShaderSourceFromFile(vertex_shader_filepath_);
    const std::string fragment_shader_source = LoadShaderSourceFromFile(fragment_shader_filepath_);

    vertex_shader_ = BuildShader(GL_VERTEX_SHADER, vertex_shader_source);
    fragment_shader_ = BuildShader(GL_FRAGMENT_SHADER, fragment_shader_source);


    program_object_ = glCreateProgram();
    glAttachShader(program_object_, vertex_shader_);
    glAttachShader(program_object_, fragment_shader_);
    glBindFragDataLocation(program_object_, 0, fragment_data_location_name.c_str());
    glLinkProgram(program_object_);
    OPENGL_DEBUG_CHECK();

    built_ = true;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"

GLuint Shader::BuildShader(GLenum shader_type, const std::string& shader_source) {
    const GLchar *shader_source_c_str = shader_source.c_str();
    GLuint result = glCreateShader(shader_type);
    glShaderSource(result, 1, &shader_source_c_str, nullptr);
    glCompileShader(result);
    OPENGL_DEBUG_CHECK();

    GLint status;
    glGetShaderiv(result, GL_COMPILE_STATUS, &status);
    OPENGL_DEBUG_CHECK();
    if (!status) {
        std::string shader_type_name;

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

        fprintf(stderr, "Shader compile error [%s].\n", shader_type_name.c_str());
        char buffer[512];
        glGetShaderInfoLog(result, 512, nullptr, buffer);
        fprintf(stderr, "%s\n", buffer);
        fflush(stderr);
    }

    return result;
}

#pragma clang diagnostic pop

void Shader::Destroy() {
    if (built_) {
        glDeleteProgram(program_object_);
        glDeleteShader(vertex_shader_); // Note: program_object を生成した段階で、これは delete 可能らしい
        glDeleteShader(fragment_shader_); // Note: program_object を生成した段階で、これは delete 可能らしい
        program_object_ = 0;
        vertex_shader_ = 0;
        fragment_shader_ = 0;
    }
    built_ = false;
}

void Shader::UseProgram() const {
    if (!built_) return;

    glUseProgram(program_object_);
    OPENGL_DEBUG_CHECK();
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"

GLint Shader::GetUniformVariableLocationFromProgramObject(
        GLuint program_object,
        const std::string& name,
        const std::string& vertex_shader_filepath,
        const std::string& fragment_shader_filepath) {

    const GLint location = glGetUniformLocation(program_object, name.c_str());
    OPENGL_DEBUG_CHECK();

    if (kRuntimeAssertion && location == -1) {
        fprintf(stderr, "The uniform variable location '%s' is not found in '%s' or '%s'.\n",
                name.c_str(),
                vertex_shader_filepath.c_str(),
                fragment_shader_filepath.c_str());
        abort();
    }
    return location;
}

#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"

GLint Shader::GetAttribVariableLocationFromProgramObject(
        GLuint program_object,
        const std::string& name,
        const std::string& vertex_shader_filepath,
        const std::string& fragment_shader_filepath) {

    const GLint location = glGetAttribLocation(program_object, name.c_str());
    OPENGL_DEBUG_CHECK();

    if (kRuntimeAssertion && location == -1) {
        fprintf(stderr, "The attribute variable location '%s' is not found in '%s' or '%s'.\n",
                name.c_str(),
                vertex_shader_filepath.c_str(),
                fragment_shader_filepath.c_str());
        abort();
    }
    return location;
}

GLint Shader::GetAttribVariableLocation(const std::string& name) const {
    if (!built_) return -1;

    // Note: もし最適化が必要になった場合は、一度取得した値をキャッシュする
    return GetAttribVariableLocationFromProgramObject(
            program_object_, name, vertex_shader_filepath_, fragment_shader_filepath_);
}

GLint Shader::GetUniformVariableLocation(const std::string& name) const {
    if (!built_) return -1;

    // Note: もし最適化が必要になった場合は、一度取得した値をキャッシュする
    return GetUniformVariableLocationFromProgramObject(
            program_object_, name, vertex_shader_filepath_, fragment_shader_filepath_);
}

Shader::~Shader() {
    try {
        Destroy();
        std::cerr << vertex_shader_filepath_ << " is destroy." << std::endl;
    } catch (...) {
        std::cerr << "(Shader) Fatal error in destructor." << std::endl;
    }
}

#pragma clang diagnostic pop
