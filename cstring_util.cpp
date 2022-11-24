//
// Created by komiyak on 22/11/25.
//

#include <cstring>
#include "cstring_util.h"
#include "debug.h"

bool cstring_util::EqualLast(const char *target, const char *keyword) {
    DEBUG_ASSERT(target != nullptr);
    DEBUG_ASSERT(keyword != nullptr);

    const std::size_t keyword_len = std::strlen(keyword);
    const std::size_t target_len = std::strlen(target);
    DEBUG_ASSERT(target_len != 0);
    DEBUG_ASSERT(keyword_len != 0);
    DEBUG_ASSERT(target_len >= keyword_len);

    // 末尾で比較
    return std::strcmp(&target[target_len - keyword_len], keyword) == 0;
}
