#include <iostream>
#include <cstdio>

#include "application.h"
#include "../debug.h"
#include "../opengl_debug.h"
#include "../key_callback_singleton.h"
#include "scene.h"

void Application::CreateWindow(std::shared_ptr<Scene> (*scene_method)()) {
    if (created_) return;

    DEBUG_ASSERT_MESSAGE(scene_method, "scene_method is required.");

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
        glDebugMessageCallback(opengl_debug::DebugMessageCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }


    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);

    // 初回起動の Activity を登録する
    std::shared_ptr<Scene> scene = scene_method();
    scenes_stack_.push(scene);
    KeyCallbackSingleton::GetInstance().SetActivity(scene);
    scene->OnAttach(application_context_);

    created_ = true;
}

void Application::Destroy() {
    if (created_) {
        // glfwDestroyWindow を実行する前に、すべての scene を削除する
        while (!scenes_stack_.empty()) {
            PopScene();
        }

        glfwDestroyWindow(glfw_window_);
        glfw_window_ = nullptr;
        glfwTerminate();
    }
    created_ = false;
}

void Application::RunLoop() {
    DEBUG_ASSERT(created_);
    DEBUG_ASSERT(glfw_window_);

    // 最初の scene を開始する
    scenes_stack_.top()->OnStart();

    // Application loop の実行
    while (!glfwWindowShouldClose(glfw_window_) && !scenes_stack_.empty()) {
        scenes_stack_.top()->OnBeforeFrame();
        scenes_stack_.top()->OnFrame();

        glfwSwapBuffers(glfw_window_);
        glfwPollEvents();

        scenes_stack_.top()->OnFrameAfterSwap();

        // Activity が終了したがっている場合は、pop する
        if (scenes_stack_.top()->IsShouldDestroy()) {
            if (scenes_stack_.top()->HaveNextScene()) {
                // Activity が push を要求している場合は、push する
                std::shared_ptr<Scene> next_scene = scenes_stack_.top()->NextScene();

                PopScene();

                scenes_stack_.push(next_scene);
                KeyCallbackSingleton::GetInstance().SetActivity(next_scene);
                next_scene->OnAttach(application_context_);
                next_scene->OnStart();
            } else {
                PopScene();
            }
        }
    }
}

void Application::ErrorCallback([[maybe_unused]] int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

void Application::KeyCallback(
        [[maybe_unused]] GLFWwindow *window,
        int key,
        [[maybe_unused]] int scancode,
        int action,
        [[maybe_unused]] int mods) {

    std::weak_ptr<Scene> scene = KeyCallbackSingleton::GetInstance().GetActivity();
    if (auto p = scene.lock()) {
        p->OnKey(key, action);
    }
}

void Application::PopScene() {
    std::shared_ptr<Scene> scene = scenes_stack_.top();
    scene->OnDestroy();
    scenes_stack_.pop(); // shared_ptr なので pop によって自動的に delete される

    if (!scenes_stack_.empty()) {
        KeyCallbackSingleton::GetInstance().SetActivity(scenes_stack_.top());
    }
}

Application::~Application() {
    try {
        Destroy();
    } catch (...) {
        std::cerr << "(Application) Fatal error in destructor." << std::endl;
    }
}
