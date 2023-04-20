#include <iostream>
#include <cstdio>

#include <execinfo.h>
#include <unistd.h>

#include "include/gl_app/gl.h"
#include "include/gl_app/application.h"
#include "include/gl_app/debug.h"
#include "include/gl_app/key_callback_singleton.h"
#include "include/gl_app/scene.h"

// OpenGL debug context 有効時に呼び出される glDebugMessageCallback 用の実装
static void APIENTRY DebugMessageCallbackForGl_(
        GLenum source,
        GLenum type,
        unsigned int id,
        GLenum severity,
        [[maybe_unused]] GLsizei length,
        const char *message,
        [[maybe_unused]] const void *userParam) {

    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    std::cout << "opengl_debug::DebugMessageCallbackForGl" << std::endl;
    std::cout << "Debug message (" << id << "): " << message << std::endl;

    switch (source) {
        case GL_DEBUG_SOURCE_API:
            std::cout << "  Source: API(GL_DEBUG_SOURCE_API)";
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            std::cout << "  Source: Window System(GL_DEBUG_SOURCE_WINDOW_SYSTEM)";
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            std::cout << "  Source: Shader Compiler(GL_DEBUG_SOURCE_SHADER_COMPILER)";
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            std::cout << "  Source: Third Party(GL_DEBUG_SOURCE_THIRD_PARTY)";
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            std::cout << "  Source: Application(GL_DEBUG_SOURCE_APPLICATION)";
            break;
        case GL_DEBUG_SOURCE_OTHER:
            std::cout << "  Source: Other(GL_DEBUG_SOURCE_OTHER)";
            break;
        default:; // nothing
    }
    std::cout << ", ";

    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            std::cout << "Type: Error(GL_DEBUG_TYPE_ERROR)";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            std::cout << "Type: Deprecated Behaviour(GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR)";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            std::cout << "Type: Undefined Behaviour(GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR)";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            std::cout << "Type: Portability(GL_DEBUG_TYPE_PORTABILITY)";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            std::cout << "Type: Performance(GL_DEBUG_TYPE_PERFORMANCE)";
            break;
        case GL_DEBUG_TYPE_MARKER:
            std::cout << "Type: Marker(GL_DEBUG_TYPE_MARKER)";
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            std::cout << "Type: Push Group(GL_DEBUG_TYPE_PUSH_GROUP)";
            break;
        case GL_DEBUG_TYPE_POP_GROUP:
            std::cout << "Type: Pop Group(GL_DEBUG_TYPE_POP_GROUP)";
            break;
        case GL_DEBUG_TYPE_OTHER:
            std::cout << "Type: Other(GL_DEBUG_TYPE_OTHER)";
            break;
        default:; // nothing
    }
    std::cout << ", ";

    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            std::cout << "Severity: high(GL_DEBUG_SEVERITY_HIGH)";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            std::cout << "Severity: medium(GL_DEBUG_SEVERITY_MEDIUM)";
            break;
        case GL_DEBUG_SEVERITY_LOW:
            std::cout << "Severity: low(GL_DEBUG_SEVERITY_LOW)";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            std::cout << "Severity: notification(GL_DEBUG_SEVERITY_NOTIFICATION)";
            break;
        default:; // nothing
    }
    std::cout << std::endl;

    // For linux platform, to get and print stacktrace.
    const int kBacktraceSize = 10;
    void *backtrace_array[kBacktraceSize];
    const int backtrace_size = backtrace(backtrace_array, kBacktraceSize);
    backtrace_symbols_fd(backtrace_array, backtrace_size, STDOUT_FILENO);

    std::cout << std::endl;
}


void gl_app::Application::CreateWindow(std::shared_ptr<Scene> (*scene_method)()) {
    if (created_) return;

    GL_APP_DEBUG_ASSERT_MESSAGE(scene_method, "scene_method is required.");

    glfwSetErrorCallback(ErrorCallback);

    if (!glfwInit()) {
        fprintf(stderr, "Error: Failed to initialize GLFW.\n");
        exit(EXIT_FAILURE);
    }

    // Requiring OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, gl_app::kOpenGLDebugContext);

    glfw_window_ = glfwCreateWindow(
            application_context_->GetWindowScreenWidth(),
            application_context_->GetWindowScreenHeight(),
            "The sandbox of OpenGL",
            nullptr,
            nullptr);
    if (!glfw_window_) {
        fprintf(stderr, "Error: Failed to make GLFW window.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Activate OpenGL context
    glfwSetKeyCallback(glfw_window_, KeyCallback);
    glfwMakeContextCurrent(glfw_window_);

    // Loading GLAD
    const int kGladResult = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    if (!kGladResult) {
        fprintf(stderr, "Error: Failed to initialize GLAD.\n");
        glfwDestroyWindow(glfw_window_);
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
        glDebugMessageCallback(DebugMessageCallbackForGl_, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }


    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);

    // 初回起動の Activity を登録する
    scene_ = scene_method();
    gl_app::KeyCallbackSingleton::GetInstance().SetActivity(scene_);
    scene_->OnAttach(application_context_);

    created_ = true;
}

void gl_app::Application::Destroy() {
    if (created_) {
        DestroySceneImmediately();

        glfwDestroyWindow(glfw_window_);
        glfw_window_ = nullptr;
        glfwTerminate();
    }
    created_ = false;
}

void gl_app::Application::RunLoop() {
    GL_APP_DEBUG_ASSERT(created_);
    GL_APP_DEBUG_ASSERT(glfw_window_);

    // 最初の scene を開始する
    scene_->OnStart();

    // Application loop の実行
    while (!glfwWindowShouldClose(glfw_window_) && scene_) {
        scene_->OnBeforeFrame();
        scene_->OnFrame();

        glfwSwapBuffers(glfw_window_);
        glfwPollEvents();

        scene_->OnFrameAfterSwap();

        // Activity が終了したがっている場合は、pop する
        if (scene_->IsShouldDestroy()) {
            if (scene_->HaveNextScene()) {
                // Activity が push を要求している場合は、push する
                std::shared_ptr<Scene> next_scene = scene_->NextScene();

                DestroySceneImmediately();
                scene_ = next_scene;

                gl_app::KeyCallbackSingleton::GetInstance().SetActivity(next_scene);
                next_scene->OnAttach(application_context_);
                next_scene->OnStart();
            } else {
                DestroySceneImmediately();
            }
        }
    }
}

void gl_app::Application::ErrorCallback([[maybe_unused]] int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

void gl_app::Application::KeyCallback(
        [[maybe_unused]] GLFWwindow *window,
        int key,
        [[maybe_unused]] int scancode,
        int action,
        [[maybe_unused]] int mods) {

    std::weak_ptr<Scene> scene = gl_app::KeyCallbackSingleton::GetInstance().GetActivity();
    if (auto p = scene.lock()) {
        p->OnKey(key, action);
    }
}

void gl_app::Application::DestroySceneImmediately() {
    if (scene_) {
        scene_->OnDestroy();
        scene_.reset(); // Note: scene_ デストラクタに OnDestroy() を仕込んでおくべきかもしれない
    }
}

gl_app::Application::~Application() {
    try {
        Destroy();
    } catch (...) {
        std::cerr << "(Application) Fatal error in destructor." << std::endl;
    }
}
