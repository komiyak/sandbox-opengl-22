#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include "opengl_debug.h"
#include "fps.h"
#include "vertex_render_object.h"
#include "shader.h"
#include "position_vertex_specification.h"
#include "color_vertex_specification.h"
#include "basic_shader_uniform.h"

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

    // Requiring OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, kOpenGLDebugContext);
    glfw_window = glfwCreateWindow(800, 600, "The sandbox of OpenGL", nullptr, nullptr);
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

    fprintf(stdout, "Your computer supports to OpenGL %d.%d (Driver: %s).\n",
            GLVersion.major,
            GLVersion.minor,
            glGetString(GL_VERSION));

    // Enabling the debug context in OpenGL.
    GLint gl_context_flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &gl_context_flags);
    if (gl_context_flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(opengl_debug::DebugMessageCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }


    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);


    // 頂点
    // Note: Projection の説明を省くために、最初から device coordinates に対応した頂点座標としておく
    const GLfloat kVertices[] = {
            // x, y, z, r, g, b
            0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    };

    const GLfloat kAxisVertices[] = {
            // x, y, z, r, g, b
            0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

            0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,

            0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f,
    };

    const GLfloat kGridPlaneVertices[] = {
            -5.0f, 0.0f, -5.f,
            -5.0f, 0.0f, 5.0f,

            -4.0f, 0.0f, -5.0f,
            -4.0f, 0.0f, 5.0f,

            -3.0f, 0.0f, -5.0f,
            -3.0f, 0.0f, 5.0f,

            -2.0f, 0.0f, -5.0f,
            -2.0f, 0.0f, 5.0f,

            -1.0f, 0.0f, -5.0f,
            -1.0f, 0.0f, 5.0f,

            0.0f, 0.0f, -5.0f,
            0.0f, 0.0f, 5.0f,

            1.0f, 0.0f, -5.0f,
            1.0f, 0.0f, 5.0f,

            2.0f, 0.0f, -5.0f,
            2.0f, 0.0f, 5.0f,

            3.0f, 0.0f, -5.0f,
            3.0f, 0.0f, 5.0f,

            4.0f, 0.0f, -5.0f,
            4.0f, 0.0f, 5.0f,

            5.0f, 0.0f, -5.0f,
            5.0f, 0.0f, 5.0f,


            -5.0f, 0.0f, -5.0f,
            5.0f, 0.0f, -5.0f,

            -5.0f, 0.0f, -4.0f,
            5.0f, 0.0f, -4.0f,

            -5.0f, 0.0f, -3.0f,
            5.0f, 0.0f, -3.0f,

            -5.0f, 0.0f, -2.0f,
            5.0f, 0.0f, -2.0f,

            -5.0f, 0.0f, -1.0f,
            5.0f, 0.0f, -1.0f,

            -5.0f, 0.0f, 0.0f,
            5.0f, 0.0f, 0.0f,

            -5.0f, 0.0f, 1.0f,
            5.0f, 0.0f, 1.0f,

            -5.0f, 0.0f, 2.0f,
            5.0f, 0.0f, 2.0f,

            -5.0f, 0.0f, 3.0f,
            5.0f, 0.0f, 3.0f,

            -5.0f, 0.0f, 4.0f,
            5.0f, 0.0f, 4.0f,

            -5.0f, 0.0f, 5.0f,
            5.0f, 0.0f, 5.0f,
    };


    auto *up_grid_shader = new Shader();
    up_grid_shader->BuildFromFile("shader/white_vertex.vert", "shader/white_vertex.frag");

    auto *up_shader = new Shader();
    up_shader->BuildFromFile("shader/vertex_color.vert", "shader/vertex_color.frag");

    BasicShaderUniform grid_shader_uniform{
            up_grid_shader->GetUniformLocationOfProjectionMat(),
            up_grid_shader->GetUniformLocationOfViewMat(),
            up_grid_shader->GetUniformLocationOfModelMat()};

    BasicShaderUniform axis_shader_uniform{
            up_shader->GetUniformLocationOfProjectionMat(),
            up_shader->GetUniformLocationOfViewMat(),
            up_shader->GetUniformLocationOfModelMat()};

    BasicShaderUniform triangle_shader_uniform{
            up_shader->GetUniformLocationOfProjectionMat(),
            up_shader->GetUniformLocationOfViewMat(),
            up_shader->GetUniformLocationOfModelMat()};


    auto *up_grid = new VertexRenderObject();
    auto *up_axis = new VertexRenderObject();
    auto *up_triangle = new VertexRenderObject();

    up_grid->Initialize(
            sizeof(kGridPlaneVertices),
            (void *) kGridPlaneVertices,
            PositionVertexSpecification{up_grid_shader->GetPositionAttribLocation()},
            up_grid_shader,
            &grid_shader_uniform,
            GL_STATIC_DRAW,
            GL_LINES,
            22 * 2);
    up_axis->Initialize(
            sizeof(kAxisVertices),
            (void *) kAxisVertices,
            ColorVertexSpecification{
                    up_shader->GetPositionAttribLocation(),
                    up_shader->GetColorAttribLocation()},
            up_shader,
            &axis_shader_uniform,
            GL_STATIC_DRAW,
            GL_LINES,
            6);
    up_triangle->Initialize(
            sizeof(kVertices),
            (void *) kVertices,
            ColorVertexSpecification{
                    up_shader->GetPositionAttribLocation(),
                    up_shader->GetColorAttribLocation()},
            up_shader,
            &triangle_shader_uniform,
            GL_STATIC_DRAW,
            GL_TRIANGLES,
            3);


    // Projection 行列を設定
    const glm::mat4 projection_mat = glm::perspective(glm::radians(45.0f), 8.f / 6.f, 1.f, 50.0f);
    grid_shader_uniform.SetProjectionMat(projection_mat);
    axis_shader_uniform.SetProjectionMat(projection_mat);
    triangle_shader_uniform.SetProjectionMat(projection_mat);


    Fps *up_fps = new Fps();
    float angle = 0;

    // Application loop
    while (!glfwWindowShouldClose(glfw_window)) {
        up_fps->StartRecord();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        angle += glm::pi<float>() * 0.25f * (float) up_fps->GetElapsedTime();

        // View 行列を設定
        const glm::mat4 view_mat = glm::lookAt(
                glm::vec3(glm::cos(angle) * 8.0f, 1.f, glm::sin(angle) * 12.0f),
                glm::vec3(0.f, 0.f, 0.f),
                glm::vec3(0.f, 1.f, 0.f));


        glm::mat4 model_mat = glm::mat4(1.0f);
        model_mat = glm::translate(model_mat, glm::vec3(0.0f, 0.5f, 0.0f));
        triangle_shader_uniform.SetViewMat(view_mat);
        triangle_shader_uniform.SetModelMat(model_mat);
        up_triangle->Render();


        grid_shader_uniform.SetViewMat(view_mat);
        grid_shader_uniform.SetModelMat(glm::mat4(1.0f));
        up_grid->Render();

        axis_shader_uniform.SetViewMat(view_mat);
        axis_shader_uniform.SetModelMat(glm::mat4(1.0f));
        up_axis->Render();


        glfwSwapBuffers(glfw_window);
        glfwPollEvents();

        up_fps->EndRecord();
    }

    FINALIZE_AND_DELETE(up_fps);
    FINALIZE_AND_DELETE(up_grid);
    FINALIZE_AND_DELETE(up_axis);
    FINALIZE_AND_DELETE(up_triangle);

    FINALIZE_AND_DELETE(up_grid_shader);
    FINALIZE_AND_DELETE(up_shader);

    glfwDestroyWindow(glfw_window);
    glfwTerminate();
    return 0;
}
