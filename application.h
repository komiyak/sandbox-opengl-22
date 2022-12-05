#ifndef SANDBOX_OPENGL_22_APPLICATION_H_
#define SANDBOX_OPENGL_22_APPLICATION_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stack>

// Deleting
#define SAFE_DELETE(p) if (p) {delete (p); (p) = nullptr;} do {} while (0)

// アプリケーション統合クラス、実装として GLFW を利用しています
class Application {
public:
    // Application クラスの状態を保持する
    class Context {
    public:
        [[nodiscard]] int GetWindowScreenWidth() const {
            return windowScreenWidth_;
        }

        [[nodiscard]] int GetWindowScreenHeight() const {
            return windowScreenHeight_;
        }

    private:
        // 現在のウィンドウのスクリーンサイズ（描画領域）の横幅ピクセルサイズ
        int windowScreenWidth_{1920}; // Note: 現在は固定値だが、将来的には動的に横幅をセットする
        // 現在のウィンドウのスクリーンサイズ（描画領域）の縦幅ピクセルサイズ
        int windowScreenHeight_{1080}; // Note: 現在は固定値だが、将来的には動的に横幅をセットする
    };

    // Application クラスの利用者が任意の処理を実行するためのクラス
    // 任意の処理の実装はインターフェースの継承先で定義する
    class Activity {
    public:
        virtual ~Activity() = default;

        void OnAttach(const Context *p_context) {
            p_context_ = p_context;
        }

        // 起動時に一度だけ実行されるコールバック
        virtual void OnStart() = 0;

        // ループのメイン処理のコールバック
        virtual void OnFrame() = 0;

        // Swapping buffers の後に呼び出されるコールバック
        virtual void OnFrameAfterSwap() {};

        // ループ終了時に一度だけ実行されるコールバック
        virtual void OnDestroy() = 0;

        // キー入力イベントで呼び出される
        virtual void OnKey(int glfw_key, int glfw_action) {};

        [[nodiscard]] bool IsShouldDestroy() const {
            return should_destroy_;
        }

        [[nodiscard]] bool HaveNextActivity() const {
            return (next_activity_);
        }

        [[nodiscard]] Activity *NextActivity() {
            return next_activity_();
        }

    protected:
        const Context *p_context_{};

        // Application に終了を通知したいとき
        bool should_destroy_{};

        // Activity 終了時に次に起動する Activity があればそれを指定しておく
        // TODO: いつかメッセージ方式に変更したい。
        Activity *(*next_activity_)(){};
    };

    // Application 初期化
    // param p_activity_factory_method 初回起動する Activity を作成する factory method
    void Initialize(Activity *(*p_activity_factory_method)());

    // Application 終了
    void Finalize();

    // Application のメインループを実行
    // この関数は、メインループが終了するまで終わりません
    void RunLoop();

    void PopActivity();

private:
    // Error handling for GLFW initialization.
    static void ErrorCallback(int error, const char *description);

    // Global key inputs handling with GLFW.
    static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

    GLFWwindow *up_glfw_window_{};

    // アプリケーションの状態
    Context context_{};

    // Activity の実行スタック (top element が常に実行される)
    std::stack<Activity *> activities_stack_{};
};

#endif //SANDBOX_OPENGL_22_APPLICATION_H_
