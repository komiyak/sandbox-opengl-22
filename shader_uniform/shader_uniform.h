#ifndef SANDBOX_OPENGL_22_SHADER_UNIFORM_H_
#define SANDBOX_OPENGL_22_SHADER_UNIFORM_H_

#include <map>
#include "../opengl_glfw.h"

// 継承先で Activate() が呼び出されると Transfer が実行されるようになる仕組みです
class ShaderUniform {
public:
    // shader に対して uniform データを送信する
    virtual void Transfer() const = 0;

    // Transfer を実行するかどうかのフラグ
    [[nodiscard]] bool IsActivated() const {
        return activated_;
    }

protected:
    void Activate() {
        activated_ = true;
    }

    // uniform variable location の値を保存する
    // この関数では重複 key の登録は assert 発生する
    void AddUniformVariableLocation(const char *key, GLint uniform_variable_location);

    // AddUniformVariableLocation() の key に index を付与する。配列のときにちょっと使いやすい
    // アイデア: index は自動付与でもいいかもね.. AddUniformVariableLocationArray() を呼び出すと、自動で配列化名で扱うとか
    void AddUniformVariableLocation(const char *key, int index, GLint uniform_variable_location);

    // uniform variable location の値を取得する
    GLint GetUniformVariableLocation(const char *key) const {
        // 登録ミスの可能性が高いため、未登録 key の場合には例外を発生させる
        return uniform_variable_locations_.at(key);
    }

    // GetUniformVariableLocation() の key に index を付与する。配列のときにちょっと使いやすい
    GLint GetUniformVariableLocation(const char *key, int index) const {
        return GetUniformVariableLocation(MakeKeyName(key, index).c_str());
    }

private:
    // key + "." + index => "key_name.0" のような名前を作る
    static std::string MakeKeyName(const char *key, int index);

    // Activate されてない場合は Transfer をコールしない
    bool activated_{};
    // uniform 変数の位置を記録する
    std::map<std::string, GLint> uniform_variable_locations_;
};

#endif //SANDBOX_OPENGL_22_SHADER_UNIFORM_H_
