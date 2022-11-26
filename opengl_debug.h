#ifndef SANDBOX_OPENGL_22_OPENGL_DEBUG_H_
#define SANDBOX_OPENGL_22_OPENGL_DEBUG_H_

#include <glad/glad.h>
#include "preference.h"

namespace opengl_debug {
    // glGetError() を実行し、エラーを検知した場合にログ出力を行う
    [[maybe_unused]] GLenum CheckError(const char *file, int line);

    // OpenGL debug context 有効時に呼び出される glDebugMessageCallback 用の実装
    [[maybe_unused]] void APIENTRY DebugMessageCallback(
            GLenum source,
            GLenum type,
            unsigned int id,
            GLenum severity,
            [[maybe_unused]] GLsizei length,
            const char *message,
            [[maybe_unused]] const void *userParam);
}


#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#define OPENGL_DEBUG_CHECK() opengl_debug::CheckError(__FILE__, __LINE__)

#pragma clang diagnostic pop

#endif //SANDBOX_OPENGL_22_OPENGL_DEBUG_H_
