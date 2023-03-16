#ifndef SANDBOX_OPENGL_22_KEY_CALLBACK_SINGLETON_H_
#define SANDBOX_OPENGL_22_KEY_CALLBACK_SINGLETON_H_

#include <memory>
#include <utility>
#include "application/application.h"

// キー入力を受け付ける singleton クラス
class KeyCallbackSingleton {
protected:
    KeyCallbackSingleton() = default;

public:
    ~KeyCallbackSingleton() = default;

    KeyCallbackSingleton(const KeyCallbackSingleton &) = delete;

    KeyCallbackSingleton &operator=(const KeyCallbackSingleton &) = delete;

    // GetFps the singleton instance.
    static KeyCallbackSingleton &GetInstance();

    void SetActivity(std::weak_ptr<Scene> activity) {
        activity_ = std::move(activity);
    }

    [[nodiscard]] std::weak_ptr<Scene> GetActivity() const {
        return activity_;
    }

protected:
    static std::unique_ptr<KeyCallbackSingleton> singleton_;

    std::weak_ptr<Scene> activity_{};
};

#endif //SANDBOX_OPENGL_22_KEY_CALLBACK_SINGLETON_H_
