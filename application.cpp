#include <cstdio>

#include "application.h"
#include "debug.h"
#include "opengl_debug.h"

void Application::Initialize(Content *p_content) {
    DEBUG_ASSERT_MESSAGE(p_content, "p_content is required.");
    p_content_ = p_content;

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

    up_glfw_window_ = glfwCreateWindow(800, 600, "The sandbox of OpenGL", nullptr, nullptr);
    if (!up_glfw_window_) {
        fprintf(stderr, "Error: Failed to make GLFW window.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Activate OpenGL context
    glfwSetKeyCallback(up_glfw_window_, KeyCallback);
    glfwMakeContextCurrent(up_glfw_window_);

    // Loading GLAD
    const int kGladResult = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    if (!kGladResult) {
        fprintf(stderr, "Error: Failed to initialize GLAD.\n");
        glfwDestroyWindow(up_glfw_window_);
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
}

void Application::Finalize() {
    glfwDestroyWindow(up_glfw_window_);
    up_glfw_window_ = nullptr;
    glfwTerminate();
}

void Application::RunLoop() const {
    DEBUG_ASSERT(up_glfw_window_);

    p_content_->OnStart();

    // Application loop の実行
    while (!glfwWindowShouldClose(up_glfw_window_)) {
        p_content_->OnFrame();

        glfwSwapBuffers(up_glfw_window_);
        glfwPollEvents();

        p_content_->OnFrameAfterSwap();
    }

    p_content_->OnDestroy();
}

void Application::ErrorCallback([[maybe_unused]] int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

void Application::KeyCallback(
        GLFWwindow *window,
        int key,
        [[maybe_unused]] int scancode,
        int action,
        [[maybe_unused]] int mods) {

    // ESC の場合はとりあえずアプリケーションを終了する
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}
