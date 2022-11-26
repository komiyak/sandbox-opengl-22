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


    // Get uniform locations
    uniform_projection_mat_ = glGetUniformLocation(program_object_, "projection_mat");
    uniform_view_mat_ = glGetUniformLocation(program_object_, "view_mat");
    uniform_model_mat_ = glGetUniformLocation(program_object_, "model_mat");
    uniform_texture_unit_ = glGetUniformLocation(program_object_, "tex");
    OPENGL_DEBUG_CHECK();

    // Get attrib locations (どうせ使うので事前に取り出しておく)
    position_attrib_location_ = glGetAttribLocation(program_object_, "position");
    color_attrib_location_ = glGetAttribLocation(program_object_, "color");
    texcoord_attrib_location_ = glGetAttribLocation(program_object_, "texcoord");
    OPENGL_DEBUG_CHECK();
}

GLuint Shader::BuildShader(GLenum shader_type, const GLchar *shader_source) {
    GLuint result = glCreateShader(shader_type);
    glShaderSource(result, 1, &shader_source, nullptr);
    glCompileShader(result);
    OPENGL_DEBUG_CHECK();


    GLint status;
    glGetShaderiv(result, GL_COMPILE_STATUS, &status);
    OPENGL_DEBUG_CHECK();
    if (!status) {
        fprintf(stderr, "shader compile error.\n");
        char buffer[512];
        glGetShaderInfoLog(result, 512, nullptr, buffer);
        fprintf(stderr, "%s", buffer);
    }

    return result;
}

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
