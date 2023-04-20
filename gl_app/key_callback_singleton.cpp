#include "include/gl_app/key_callback_singleton.h"

std::unique_ptr<gl_app::KeyCallbackSingleton> gl_app::KeyCallbackSingleton::singleton_ = nullptr;

gl_app::KeyCallbackSingleton &gl_app::KeyCallbackSingleton::GetInstance() {
    if (singleton_ == nullptr) {
        singleton_ = std::unique_ptr<KeyCallbackSingleton>{new KeyCallbackSingleton()};
    }
    return *singleton_;
}
