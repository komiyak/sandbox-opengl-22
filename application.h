#ifndef SANDBOX_OPENGL_22_APPLICATION_H_
#define SANDBOX_OPENGL_22_APPLICATION_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// アプリケーション統合クラス、実装として GLFW を利用しています
class Application {
public:
    class Loop {
    public:
        // アプリケーションループのメイン処理
        virtual void OnMain() = 0;

        // Swapping buffers 後に呼び出されるコールバック
        virtual void OnAfterSwappingBuffers() = 0;

        // Application ループの終了処理
        virtual void Finalize() = 0;
    };

    // Application 初期化
    // param p_loop アプリケーションループの実態
    void Initialize(Loop *p_loop);

    // Application 終了
    void Finalize();

    // Application のメインループを実行
    // この関数は、メインループが終了するまで終わりません
    void RunLoop() const;


private:
    // Error handling for GLFW initialization.
    static void ErrorCallback(int error, const char *description);

    // Global key inputs handling with GLFW.
    static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

    GLFWwindow *up_glfw_window_{};

    // アプリケーションループのコールバック実装
    Loop *p_loop_{};
};

#endif //SANDBOX_OPENGL_22_APPLICATION_H_
