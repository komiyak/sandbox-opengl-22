#ifndef SANDBOX_OPENGL_22_SHADER_UNIFORM_H_
#define SANDBOX_OPENGL_22_SHADER_UNIFORM_H_

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

private:
    // Activate されてない場合は Transfer をコールしない
    bool activated_{};
};

#endif //SANDBOX_OPENGL_22_SHADER_UNIFORM_H_
