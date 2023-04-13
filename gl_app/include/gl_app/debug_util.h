#ifndef SANDBOX_OPENGL_22_GL_APP_DEBUG_UTIL_H_
#define SANDBOX_OPENGL_22_GL_APP_DEBUG_UTIL_H_

#include <glad/glad.h>

namespace gl_app {
    // glGetError() を実行し、エラーを検知した場合にログ出力を行う
    [[maybe_unused]] void CheckGlError(const char *file, int line);

    // OpenGL debug context 有効時に呼び出される glDebugMessageCallback 用の実装
    [[maybe_unused]] void APIENTRY DebugMessageCallbackForGl(
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

#define GL_APP_CHECK_GL_ERROR() gl_app::CheckGlError(__FILE__, __LINE__)

#pragma clang diagnostic pop

#endif //SANDBOX_OPENGL_22_GL_APP_DEBUG_UTIL_H_
