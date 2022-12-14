#ifndef SANDBOX_OPENGL_22_SCENE_H_
#define SANDBOX_OPENGL_22_SCENE_H_

class ApplicationContext;

// Application クラスから利用される任意の Scene の基底クラス
class Scene {
public:
    virtual ~Scene() = default;

    void OnAttach(const ApplicationContext *p_context) {
        p_application_context_ = p_context;
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

    [[nodiscard]] bool HaveNextScene() const {
        return (next_scene_);
    }

    [[nodiscard]] Scene *NextScene() {
        return next_scene_();
    }

protected:
    const ApplicationContext *p_application_context_{};

    // Application に終了を通知したいとき
    bool should_destroy_{};

    // Scene 終了時に次に起動する Scene があればそれを指定しておく
    // TODO: いつかメッセージ方式に変更したい。
    Scene *(*next_scene_)(){};
};


#endif //SANDBOX_OPENGL_22_SCENE_H_
