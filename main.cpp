#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const GLchar *kVertexSource =
        "#version 150 core\n" // GLSL 1.5
        "in vec2 position;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(position, 0.0, 1.0);\n"
        "}\n";

const GLchar *kFragmentSource =
        "#version 150 core\n" // GLSL 1.5
        "out vec4 outColor;\n"
        "void main()\n"
        "{\n"
        "    outColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
        "}\n";

/**
 * Error handling for GLFW initialization.
 */
static void ErrorCallback(__attribute__((unused)) int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

/**
 * Global key inputs handling with GLFW.
 */
static void KeyCallback(
        GLFWwindow *window,
        int key,
        __attribute__((unused)) int scancode,
        int action,
        __attribute__((unused)) int mods) {

    // ESC の場合はとりあえずアプリケーションを終了する
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main() {
    // The main window handle
    GLFWwindow *glfw_window;

    glfwSetErrorCallback(ErrorCallback);

    if (!glfwInit()) {
        fprintf(stderr, "Error: Failed to initialize GLFW.\n");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfw_window = glfwCreateWindow(640, 480, "Simple OpenGL 3.2", NULL, NULL);
    if (!glfw_window) {
        fprintf(stderr, "Error: Failed to make GLFW window.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Activate OpenGL context
    glfwSetKeyCallback(glfw_window, KeyCallback);
    glfwMakeContextCurrent(glfw_window);

    // Loading GLAD
    const int kGladResult = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    if (!kGladResult) {
        fprintf(stderr, "Error: Failed to initialize GLAD.\n");
        glfwDestroyWindow(glfw_window);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "Your GLAD supports to OpenGL version %d.%d.\n", GLVersion.major, GLVersion.minor);

    glfwSwapInterval(1);


    // Create VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create a VBO
    GLuint vbo;
    glGenBuffers(1, &vbo);

    // 頂点
    // Note: Projection の説明を省くために、最初から device coordinates に対応した頂点座標としておく
    const GLfloat kVertices[] = {
            0.0f, 0.5f,
            0.5f, -0.5f,
            -0.5f, -0.5f
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kVertices), kVertices, GL_STATIC_DRAW);


    // Vertex shader setup
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &kVertexSource, NULL);
    glCompileShader(vertex_shader);

    GLint status;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        fprintf(stderr, "vertex shader compile error.\n");
        char buffer[512];
        glGetShaderInfoLog(vertex_shader, 512, NULL, buffer);
        fprintf(stderr, "%s", buffer);
    }

    // Fragment shader setup
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &kFragmentSource, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        fprintf(stderr, "fragment shader compile error.\n");
        char buffer[512];
        glGetShaderInfoLog(vertex_shader, 512, NULL, buffer);
        fprintf(stderr, "%s", buffer);
    }

    // Combining shaders into a program.
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glBindFragDataLocation(shader_program, 0, "outColor");
    glLinkProgram(shader_program);
    glUseProgram(shader_program);

    // Specify the layout of the vertex data
    GLint pos_attrib = glGetAttribLocation(shader_program, "position");
    glEnableVertexAttribArray(pos_attrib);
    glVertexAttribPointer(pos_attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);


    // Application loop
    while (!glfwWindowShouldClose(glfw_window)) {
        int width;
        int height;
        glfwGetFramebufferSize(glfw_window, &width, &height);
        //glViewport(0, 0, width, height);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(glfw_window);
        glfwPollEvents();
    }

    glDeleteProgram(shader_program);
    glDeleteShader(fragment_shader);
    glDeleteShader(vertex_shader);

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    glfwDestroyWindow(glfw_window);
    glfwTerminate();
    return 0;
}
