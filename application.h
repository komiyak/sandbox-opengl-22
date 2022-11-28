#ifndef SANDBOX_OPENGL_22_APPLICATION_H_
#define SANDBOX_OPENGL_22_APPLICATION_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// アプリケーション統合クラス、実装として GLFW を利用しています
class Application {
public:
    // Application クラスの利用者が任意の処理を実行するためのクラス
    // 任意の処理の実装はインターフェースの継承先で定義する
    class Content {
    public:
        // 起動時に一度だけ実行されるコールバック
        virtual void OnStart() = 0;

        // ループのメイン処理のコールバック
        virtual void OnFrame() = 0;

        // Swapping buffers の後に呼び出されるコールバック
        virtual void OnFrameAfterSwap() = 0;

        // ループ終了時に一度だけ実行されるコールバック
        virtual void OnDestroy() = 0;
    };

    // Application 初期化
    // param p_content アプリケーションループの実態
    void Initialize(Content *p_content);

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

    // アプリケーション実装
    Content *p_content_{};
};

#endif //SANDBOX_OPENGL_22_APPLICATION_H_
