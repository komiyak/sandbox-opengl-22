#ifndef SANDBOX_OPENGL_22_SHADER_UNIFORM_H_
#define SANDBOX_OPENGL_22_SHADER_UNIFORM_H_

#include <map>
#include <memory>
#include <string>
#include <utility>
#include "../opengl_glfw.h"

class Shader;

// 継承先で Activate() が呼び出されると Transfer が実行されるようになる仕組みです
class ShaderUniform {
public:
    ShaderUniform() = default;

    virtual ~ShaderUniform() = default;

    // shader に対して uniform データを送信する
    virtual void Transfer() const = 0;

    // Transfer を実行するかどうかのフラグ
    [[nodiscard]] bool IsActivated() const {
        return activated_;
    }

    // 利用する shader を指定する
    // shader uniform を利用するために必ず設定が必要
    void SetShader(std::weak_ptr<Shader> shader) {
        shader_ = std::move(shader);
        activated_ = true;
    }

protected:
    [[nodiscard]] GLint GetUniformVariableLocation(const std::string& name) const;

    // Short name of GetUniformVariableLocation()
    [[nodiscard]] GLint Location(const std::string& name) const {
        return GetUniformVariableLocation(name);
    }

private:
    // Activate されてない場合は Transfer をコールしない
    bool activated_{};

    // uniform variable location を取得する任意の shader
    std::weak_ptr<Shader> shader_{};
};

#endif //SANDBOX_OPENGL_22_SHADER_UNIFORM_H_
