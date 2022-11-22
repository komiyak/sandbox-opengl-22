#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include "fps.h"

#include "vertex_render_object.h"
#include "shader.h"
#include "position_vertex_specification.h"


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
    glfw_window = glfwCreateWindow(800, 600, "Simple OpenGL 3.2", NULL, NULL);
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



    // 頂点
    // Note: Projection の説明を省くために、最初から device coordinates に対応した頂点座標としておく
    const GLfloat kVertices[] = {
            0.0f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
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

    auto *up_grid = new VertexRenderObject();
    auto *up_triangle = new VertexRenderObject();

    auto *up_shader = new Shader();
    up_shader->LoadFromFile("shader/vertex_color.vert", "shader/vertex_color.frag");

    auto *up_xyz_axis_shader = new Shader();
    up_xyz_axis_shader->LoadFromFile("shader/vertex_color_xyz_axis.vert", "shader/vertex_color_xyz_axis.frag");

    up_grid->Initialize(
            sizeof(kGridPlaneVertices),
            (void *) kGridPlaneVertices,
            PositionVertexSpecification{up_shader->GetPositionAttribLocation()},
            *up_shader,
            GL_STATIC_DRAW,
            GL_LINES,
            22 * 2);
    up_triangle->Initialize(
            sizeof(kVertices),
            (void *) kVertices,
            PositionVertexSpecification{up_shader->GetPositionAttribLocation()},
            *up_shader,
            GL_STATIC_DRAW,
            GL_TRIANGLES,
            3);


    // Projection 行列を設定
    const glm::mat4 projection_mat = glm::perspective(glm::radians(45.0f), 8.f / 6.f, 1.f, 50.0f);
    glUniformMatrix4fv(up_shader->GetUniformLocationOfProjectionMat(), 1, GL_FALSE, glm::value_ptr(projection_mat));

    Fps *up_fps = new Fps();

    float angle = 0;

    // Application loop
    while (!glfwWindowShouldClose(glfw_window)) {
        up_fps->StartRecord();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        angle += glm::pi<float>() * 0.25f * (float) up_fps->GetElapsedTime();

        up_shader->Use();

        // View 行列を設定
        const glm::mat4 view_mat = glm::lookAt(
                glm::vec3(glm::cos(angle) * 8.0f, 1.f, glm::sin(angle) * 12.0f),
                glm::vec3(0.f, 0.f, 0.f),
                glm::vec3(0.f, 1.f, 0.f));
        glUniformMatrix4fv(up_shader->GetUniformLocationOfViewMat(), 1, GL_FALSE, glm::value_ptr(view_mat));


        glm::mat4 model_mat = glm::mat4(1.0f);
        glUniformMatrix4fv(up_shader->GetUniformLocationOfModelMat(), 1, GL_FALSE, glm::value_ptr(model_mat));
        up_triangle->Draw();


        glm::mat4 model_mat_2 = glm::mat4(1.0f);
        glUniformMatrix4fv(up_shader->GetUniformLocationOfModelMat(), 1, GL_FALSE, glm::value_ptr(model_mat_2));
        up_grid->Draw();


        glfwSwapBuffers(glfw_window);
        glfwPollEvents();

        up_fps->EndRecord();
    }

    FINALIZE_AND_DELETE(up_fps);
    FINALIZE_AND_DELETE(up_grid);
    FINALIZE_AND_DELETE(up_triangle);

    FINALIZE_AND_DELETE(up_shader);
    FINALIZE_AND_DELETE(up_xyz_axis_shader);

    glfwDestroyWindow(glfw_window);
    glfwTerminate();
    return 0;
}
