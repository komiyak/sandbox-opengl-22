#ifndef SANDBOX_OPENGL_22_GL_APP_GL_DEBUG_H_
#define SANDBOX_OPENGL_22_GL_APP_GL_DEBUG_H_

#include <string>

namespace gl_app {
    // glGetError() を実行し、エラーを検知した場合にログ出力を行う
    [[maybe_unused]] void CheckGlError(const std::string &file, int line);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

// gl_app::CheckGlError() 実行用マクロ
#define GL_APP_CHECK_GL_ERROR() gl_app::CheckGlError(__FILE__, __LINE__)

#pragma clang diagnostic pop

#endif //SANDBOX_OPENGL_22_GL_APP_GL_DEBUG_H_
