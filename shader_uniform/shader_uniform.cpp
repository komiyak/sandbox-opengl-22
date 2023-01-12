#include "shader_uniform.h"
#include "../debug.h"

void ShaderUniform::AddUniformVariableLocation(const char *key, GLint uniform_variable_location) {
    DEBUG_ASSERT(key);
    DEBUG_ASSERT_MESSAGE(uniform_variable_location != -1, "Invalid value of the uniform variable location.");
    auto [iter, b] = uniform_variable_locations_.try_emplace(key, uniform_variable_location);

    // 重複 key の登録は許さない（ほとんどの場合で key の登録は手作業になるので、たぶん入力ミスだからエラーでよい）
    DEBUG_ASSERT_MESSAGE(b, "Insert duplicate key.");
}

void ShaderUniform::AddUniformVariableLocation(const char *key, int index, GLint uniform_variable_location) {
    return AddUniformVariableLocation(MakeKeyName(key, index).c_str(), uniform_variable_location);
}

std::string ShaderUniform::MakeKeyName(const char *key, int index) {
    DEBUG_ASSERT(0 <= index);
    DEBUG_ASSERT(key);
    // A better way: https://stackoverflow.com/a/900035
    return std::string(key) + std::string(".") + std::to_string(index);
}
