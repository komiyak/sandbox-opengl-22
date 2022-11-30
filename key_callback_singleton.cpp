#include "key_callback_singleton.h"

KeyCallbackSingleton *KeyCallbackSingleton::singleton_ = nullptr;

KeyCallbackSingleton *KeyCallbackSingleton::GetInstance() {
    if (singleton_ == nullptr) {
        singleton_ = new KeyCallbackSingleton();
    }
    return singleton_;
}
