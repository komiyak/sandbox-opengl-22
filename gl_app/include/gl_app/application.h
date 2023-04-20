#ifndef SANDBOX_OPENGL_22_GL_APP_APPLICATION_H_
#define SANDBOX_OPENGL_22_GL_APP_APPLICATION_H_

#include <memory>

#include "application_context.h"
#include "scene.h"

struct GLFWwindow;

namespace gl_app {
    // アプリケーション統合クラス、実装として GLFW を利用しています
    class Application {
    public:
        Application() = default;

        ~Application();

        Application(const Application &) = delete;

        Application &operator=(const Application &) = delete;

        // Window を起動する
        // param scene_method 初回起動する Scene を作成する factory method
        void CreateWindow(std::shared_ptr<gl_app::Scene> (*scene_method)());

        // 終了処理
        void Destroy();

        // Application のメインループを実行
        // この関数は、メインループが終了するまで終わりません
        void RunLoop();

    private:
        void DestroySceneImmediately();

        // Error handling for GLFW initialization.
        static void ErrorCallback(int error, const char *description);

        // Global key inputs handling with GLFW.
        static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

        bool created_{};

        // GLFW で作成したウィンドウオブジェクト
        GLFWwindow *glfw_window_{};

        // アプリケーションの状態
        std::shared_ptr<gl_app::ApplicationContext> application_context_{new gl_app::ApplicationContext()};

        // 実行中の scene
        // Note: 複数のシーンを管理できる構造も考えたが、複数のシーンを生かしておく活用方法があまり思いつかないため、
        // 初期の実装としてはシンプルに一つだけ管理すればよいという方式にしました。
        std::shared_ptr<gl_app::Scene> scene_{}; // TODO: shared_ptr => unique_ptr ? key handler 実装に対して weak_ptr scene を共有しなければならない...。message 機構か...
    };
}

#endif //SANDBOX_OPENGL_22_GL_APP_APPLICATION_H_
