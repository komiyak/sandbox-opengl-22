#ifndef SANDBOX_OPENGL_22_CSTRING_UTIL_H_
#define SANDBOX_OPENGL_22_CSTRING_UTIL_H_

namespace cstring_util {
    // 文字列の末尾が keyword と一致するかどうかを比較する
    // target 探す文字列
    // keyword 対象の文字列
    bool EqualLast(const char *target, const char *keyword);
}

#endif //SANDBOX_OPENGL_22_CSTRING_UTIL_H_
