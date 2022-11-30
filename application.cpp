#include <cstdio>

#include "application.h"
#include "debug.h"
#include "opengl_debug.h"
#include "key_callback_singleton.h"

void Application::Initialize(Application::Activity *(*p_activity_factory_method)()) {
    DEBUG_ASSERT_MESSAGE(p_activity_factory_method, "p_activity_factory_method is required.");

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

    up_glfw_window_ = glfwCreateWindow(
            context_.GetWindowScreenWidth(),
            context_.GetWindowScreenHeight(),
            "The sandbox of OpenGL",
            nullptr,
            nullptr);
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

    fprintf(stdout,
            "Your computer supports to OpenGL %d.%d (Driver: %s).\n",
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

    // 初回起動の Activity を登録する
    Activity *up_activity = p_activity_factory_method();
    DEBUG_ASSERT(up_activity);
    activities_stack_.push(up_activity);
    KeyCallbackSingleton::GetInstance()->SetActivity(up_activity);
    up_activity->OnAttach(&context_);
}

void Application::Finalize() {
    // 終了時には必ず stack を空っぽにする
    while (!activities_stack_.empty()) {
        PopActivity();
    }

    glfwDestroyWindow(up_glfw_window_);
    up_glfw_window_ = nullptr;
    glfwTerminate();
}

void Application::RunLoop() {
    DEBUG_ASSERT(up_glfw_window_);

    // 最初の activity を開始する
    activities_stack_.top()->OnStart();

    // Application loop の実行
    while (!glfwWindowShouldClose(up_glfw_window_) && !activities_stack_.empty()) {
        activities_stack_.top()->OnFrame();

        glfwSwapBuffers(up_glfw_window_);
        glfwPollEvents();

        activities_stack_.top()->OnFrameAfterSwap();

        // Activity が終了したがっている場合は、pop する
        if (activities_stack_.top()->IsShouldDestroy()) {
            PopActivity();
        }
    }
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

    Activity *p_activity = KeyCallbackSingleton::GetInstance()->GetActivity();
    if (p_activity) {
        p_activity->OnKey(key, action);
    }
}

void Application::PopActivity() {
    Activity *p_activity = activities_stack_.top();
    p_activity->OnDestroy();
    delete p_activity; // Factory method で new しているため、ここで delete する
    activities_stack_.pop();

    if (!activities_stack_.empty()) {
        KeyCallbackSingleton::GetInstance()->SetActivity(activities_stack_.top());
    }
}
