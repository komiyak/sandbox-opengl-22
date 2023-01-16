#ifndef SANDBOX_OPENGL_22_SHADER_UNIFORM_H_
#define SANDBOX_OPENGL_22_SHADER_UNIFORM_H_

#include <map>
#include "../opengl_glfw.h"

class Shader;

// 継承先で Activate() が呼び出されると Transfer が実行されるようになる仕組みです
class ShaderUniform {
public:
    // shader に対して uniform データを送信する
    virtual void Transfer() const = 0;

    // Transfer を実行するかどうかのフラグ
    [[nodiscard]] bool IsActivated() const {
        return activated_;
    }

    // 利用する shader 参照
    void SetShader(const Shader *p_shader) {
        p_shader_ = p_shader;
        Activate();
    }

protected:
    void Activate() {
        activated_ = true;
    }

    GLint GetUniformVariableLocation(const char *name) const;

    // Short name of GetUniformVariableLocation()
    GLint Location(const char *name) const {
        return GetUniformVariableLocation(name);
    }

private:
    // Activate されてない場合は Transfer をコールしない
    bool activated_{};
    // uniform variable location を取得する任意の shader
    const Shader *p_shader_;
};

#endif //SANDBOX_OPENGL_22_SHADER_UNIFORM_H_
