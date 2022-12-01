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

void Shader::BuildFromFile(const char *vertex_shader_filepath, const char *fragment_shader_filepath) {
    DEBUG_ASSERT_MESSAGE(
            cstring_util::EqualLast(vertex_shader_filepath, ".vert"),
            "Vertex shader file must be with '.vert' extension.");
    DEBUG_ASSERT_MESSAGE(
            cstring_util::EqualLast(fragment_shader_filepath, ".frag"),
            "Vertex shader file must be with '.frag' extension.");

    const std::string vertex_shader_source = LoadShaderSourceFromFile(vertex_shader_filepath);
    const std::string fragment_shader_source = LoadShaderSourceFromFile(fragment_shader_filepath);

    vertex_shader_ = BuildShader(GL_VERTEX_SHADER, vertex_shader_source.c_str());
    fragment_shader_ = BuildShader(GL_FRAGMENT_SHADER, fragment_shader_source.c_str());


    program_object_ = glCreateProgram();
    glAttachShader(program_object_, vertex_shader_);
    glAttachShader(program_object_, fragment_shader_);
    glBindFragDataLocation(program_object_, 0, "outColor"); // outColor に色を出力する
    glLinkProgram(program_object_);
    OPENGL_DEBUG_CHECK();


    // GetFps locations of the uniform variable. (shader から取得できなかった場合は -1)
    projection_mat_uniform_location_ = glGetUniformLocation(program_object_, "projection_mat");
    view_mat_uniform_location_ = glGetUniformLocation(program_object_, "view_mat");
    model_mat_uniform_location_ = glGetUniformLocation(program_object_, "model_mat");
    texture_unit_uniform_location_ = glGetUniformLocation(program_object_, "tex");
    color_uniform_location_ = glGetUniformLocation(program_object_, "color");
    translation_vec_uniform_location_ = glGetUniformLocation(program_object_, "translation_vec");
    scaling_vec_uniform_location_ = glGetUniformLocation(program_object_, "scaling_vec");
    texcoord_translation_vec_uniform_location_ = glGetUniformLocation(program_object_, "texcoord_translation_vec");
    texcoord_scaling_vec_uniform_location_ = glGetUniformLocation(program_object_, "texcoord_scaling_vec");
    OPENGL_DEBUG_CHECK();

    // GetFps locations of the attribute variable. (shader から取得できなかった場合は -1)
    position_attrib_variable_location_ = glGetAttribLocation(program_object_, "position");
    color_attrib_variable_location_ = glGetAttribLocation(program_object_, "color");
    texcoord_attrib_variable_location_ = glGetAttribLocation(program_object_, "texcoord");
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
    glDeleteProgram(program_object_);
    glDeleteShader(vertex_shader_);
    glDeleteShader(fragment_shader_);
    program_object_ = 0;
    vertex_shader_ = 0;
    fragment_shader_ = 0;
}

void Shader::UseProgram() const {
    glUseProgram(program_object_);
    OPENGL_DEBUG_CHECK();
}
