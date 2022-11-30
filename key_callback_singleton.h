#ifndef SANDBOX_OPENGL_22_KEY_CALLBACK_SINGLETON_H_
#define SANDBOX_OPENGL_22_KEY_CALLBACK_SINGLETON_H_

#include "application.h"

// キー入力を受け付ける singleton クラス
class KeyCallbackSingleton {
public:
    KeyCallbackSingleton(KeyCallbackSingleton &key_callback_singleton) = delete;

    void operator=(const KeyCallbackSingleton &) = delete;

    // Get the singleton instance.
    static KeyCallbackSingleton *GetInstance();

    void SetActivity(Application::Activity *p_activity) {
        p_activity_ = p_activity;
    }

    [[nodiscard]] Application::Activity *GetActivity() const {
        return p_activity_;
    }

protected:
    KeyCallbackSingleton() = default;

    static KeyCallbackSingleton *singleton_;

    Application::Activity *p_activity_;
};

#endif //SANDBOX_OPENGL_22_KEY_CALLBACK_SINGLETON_H_
