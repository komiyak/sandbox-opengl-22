#include "key_callback_singleton.h"

std::unique_ptr<KeyCallbackSingleton> KeyCallbackSingleton::singleton_ = nullptr;

KeyCallbackSingleton &KeyCallbackSingleton::GetInstance() {
    if (singleton_ == nullptr) {
        singleton_ = std::unique_ptr<KeyCallbackSingleton>{new KeyCallbackSingleton()};
    }
    return *singleton_;
}
