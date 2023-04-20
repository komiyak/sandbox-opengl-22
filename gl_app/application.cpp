#include <iostream>
#include <cstdio>

#include "include/gl_app/application.h"
#include "include/gl_app/debug.h"
#include "include/gl_app/debug_util.h"
#include "include/gl_app/key_callback_singleton.h"
#include "include/gl_app/scene.h"

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
        glDebugMessageCallback(gl_app::DebugMessageCallbackForGl, nullptr);
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
