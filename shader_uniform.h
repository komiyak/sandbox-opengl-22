#ifndef SANDBOX_OPENGL_22_SHADER_UNIFORM_H_
#define SANDBOX_OPENGL_22_SHADER_UNIFORM_H_

class ShaderUniform {
public:
    // shader に対して uniform データを送信する
    virtual void Transfer() const = 0;
};

#endif //SANDBOX_OPENGL_22_SHADER_UNIFORM_H_
