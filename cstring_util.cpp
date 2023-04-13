#include <cstring>
#include <gl_app/debug.h>
#include "cstring_util.h"

bool cstring_util::EqualLast(const char *target, const char *keyword) {
    GL_APP_DEBUG_ASSERT(target != nullptr);
    GL_APP_DEBUG_ASSERT(keyword != nullptr);

    const std::size_t keyword_len = std::strlen(keyword);
    const std::size_t target_len = std::strlen(target);
    GL_APP_DEBUG_ASSERT(target_len != 0);
    GL_APP_DEBUG_ASSERT(keyword_len != 0);
    GL_APP_DEBUG_ASSERT(target_len >= keyword_len);

    // 末尾で比較
    return std::strcmp(&target[target_len - keyword_len], keyword) == 0;
}
