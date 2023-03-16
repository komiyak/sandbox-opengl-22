#ifndef SANDBOX_OPENGL_22_APPLICATION_H_
#define SANDBOX_OPENGL_22_APPLICATION_H_

#include <memory>
#include <stack>
#include "../opengl_glfw.h"

#include "application_context.h"

class Scene;

// アプリケーション統合クラス、実装として GLFW を利用しています
class Application {
public:
    Application() = default;

    ~Application();

    Application(const Application &) = delete;

    Application &operator=(const Application &) = delete;

    // Window を起動する
    // param scene_method 初回起動する Scene を作成する factory method
    void CreateWindow(std::shared_ptr<Scene> (*scene_method)());

    // 終了処理
    void Destroy();

    // Application のメインループを実行
    // この関数は、メインループが終了するまで終わりません
    void RunLoop();

private:
    void PopScene();

    // Error handling for GLFW initialization.
    static void ErrorCallback(int error, const char *description);

    // Global key inputs handling with GLFW.
    static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

    bool created_{};

    // GLFW で作成したウィンドウオブジェクト
    GLFWwindow *glfw_window_{};

    // アプリケーションの状態
    std::shared_ptr<ApplicationContext> application_context_{new ApplicationContext};

    // Activity の実行スタック (top element が常に実行される)
    std::stack<std::shared_ptr<Scene>> scenes_stack_{};
};

#endif //SANDBOX_OPENGL_22_APPLICATION_H_
