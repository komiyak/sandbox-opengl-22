#ifndef SANDBOX_OPENGL_22_KEY_CALLBACK_SINGLETON_H_
#define SANDBOX_OPENGL_22_KEY_CALLBACK_SINGLETON_H_

#include "application/application.h"

// キー入力を受け付ける singleton クラス
class KeyCallbackSingleton {
public:
    KeyCallbackSingleton(KeyCallbackSingleton &key_callback_singleton) = delete;

    void operator=(const KeyCallbackSingleton &) = delete;

    // GetFps the singleton instance.
    static KeyCallbackSingleton *GetInstance();

    void SetActivity(Scene *p_activity) {
        p_activity_ = p_activity;
    }

    [[nodiscard]] Scene *GetActivity() const {
        return p_activity_;
    }

protected:
    KeyCallbackSingleton() = default;

    static KeyCallbackSingleton *singleton_;

    Scene *p_activity_;
};

#endif //SANDBOX_OPENGL_22_KEY_CALLBACK_SINGLETON_H_
