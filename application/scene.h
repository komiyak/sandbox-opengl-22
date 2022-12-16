#ifndef SANDBOX_OPENGL_22_SCENE_H_
#define SANDBOX_OPENGL_22_SCENE_H_

#include "frame.h"

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

    // OnFrame の前に呼び出されるコールバック
    void OnBeforeFrame() {
        frame_.StartFrame();
    };

    // Swapping buffers の後に呼び出されるコールバック
    void OnFrameAfterSwap() {
        frame_.EndFrame();
    };

    // ループ終了時に一度だけ実行されるコールバック
    virtual void OnDestroy() = 0;

    // キー入力イベントで呼び出される
    virtual void OnKey(int glfw_key, int glfw_action) = 0;

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
    [[maybe_unused]] [[nodiscard]] const Frame &GetFrame() const {
        return frame_;
    }

    // Scene を終了したいときにコールする
    void SendToDestroy() {
        should_destroy_ = true;
    }

    void LaunchNextScene(Scene *(*next_scene)()) {
        should_destroy_ = true;
        next_scene_ = next_scene;
    }

    [[nodiscard]] const ApplicationContext *GetApplicationContext() const {
        return p_application_context_;
    }

private:
    // フレーム管理
    Frame frame_;

    // アプリケーションコンテキストへのリンク
    const ApplicationContext *p_application_context_{};

    // Application に終了を通知したいとき
    bool should_destroy_{};

    // Scene 終了時に次に起動する Scene があればそれを指定しておく
    // TODO: いつかメッセージ方式に変更したい。
    Scene *(*next_scene_)(){};

};

#endif //SANDBOX_OPENGL_22_SCENE_H_
