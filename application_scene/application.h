#ifndef SANDBOX_OPENGL_22_APPLICATION_H_
#define SANDBOX_OPENGL_22_APPLICATION_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stack>

#include "application_context.h"

class Scene;

// Deleting
#define SAFE_DELETE(p) if (p) {delete (p); (p) = nullptr;} do {} while (0)

// アプリケーション統合クラス、実装として GLFW を利用しています
class Application {
public:
    // Application 初期化
    // param p_scene_method 初回起動する Scene を作成する factory method
    void Initialize(Scene *(*p_scene_method)());

    // Application 終了
    void Finalize();

    // Application のメインループを実行
    // この関数は、メインループが終了するまで終わりません
    void RunLoop();

private:
    void PopScene();

    // Error handling for GLFW initialization.
    static void ErrorCallback(int error, const char *description);

    // Global key inputs handling with GLFW.
    static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

    GLFWwindow *up_glfw_window_{};

    // アプリケーションの状態
    ApplicationContext application_context_{};

    // Activity の実行スタック (top element が常に実行される)
    std::stack<Scene *> scenes_stack_{};
};

#endif //SANDBOX_OPENGL_22_APPLICATION_H_
