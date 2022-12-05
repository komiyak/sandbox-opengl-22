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

#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"

void Shader::BuildFromFile(
        const char *vertex_shader_filepath,
        const char *fragment_shader_filepath,
        const char *const *attrib_variable_location_names,
        std::size_t attrib_variable_location_names_size,
        const char *const *uniform_variable_location_names,
        std::size_t uniform_variable_location_names_size) {

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


    // Get locations of the uniform variable.
    for (int i = 0; i < uniform_variable_location_names_size; i++) {
        const char *const name = uniform_variable_location_names[i];
        const GLint location = glGetUniformLocation(program_object_, name);
        if (kRuntimeAssertion && location == -1) {
            fprintf(stderr, "The uniform variable location '%s' is not found in '%s' or '%s'.\n",
                    name,
                    vertex_shader_filepath,
                    fragment_shader_filepath);
            abort();
        }
        uniform_variable_locations_.insert(std::make_pair(name, location));
    }
    OPENGL_DEBUG_CHECK();

    // Get locations of the attribute variable.
    for (int i = 0; i < attrib_variable_location_names_size; i++) {
        const char *const name = attrib_variable_location_names[i];
        const GLint location = glGetAttribLocation(program_object_, name);
        if (kRuntimeAssertion && location == -1) {
            fprintf(stderr, "The attribute variable location '%s' is not found in '%s' or '%s'.\n",
                    name,
                    vertex_shader_filepath,
                    fragment_shader_filepath);
            abort();
        }
        attrib_variable_locations_.insert(std::make_pair(name, location));
    }
    OPENGL_DEBUG_CHECK();
}

#pragma clang diagnostic pop

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
