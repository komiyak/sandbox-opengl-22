#ifndef SANDBOX_OPENGL_22_APPLICATION_IMPLEMENTATION_H_
#define SANDBOX_OPENGL_22_APPLICATION_IMPLEMENTATION_H_

#include "application.h"
#include "frame.h"

class BasicShaderUniform;

class TextureShaderUniform;

class VertexRenderObject;

class Shader;

class ApplicationImplementation : public Application::Loop {
public:
    void OnMain() override;

    void OnAfterSwappingBuffers() override;

    void Finalize() override;

private:
    void Initialize();

    // 初回実行時（初期化管理用）
    bool first_time_{true};

    Frame *up_frame_{new Frame()};

    float angle_{0.f};

    GLuint texture_{};

    BasicShaderUniform *up_grid_shader_uniform_{};
    BasicShaderUniform *up_axis_shader_uniform_{};
    BasicShaderUniform *up_triangle_shader_uniform_{};
    TextureShaderUniform *up_grass_shader_uniform_{};

    VertexRenderObject *up_grid_{};
    VertexRenderObject *up_axis_{};
    VertexRenderObject *up_triangle_{};
    VertexRenderObject *up_grass_{};

    Shader *up_grid_shader_{};
    Shader *up_shader_{};
    Shader *up_texture_shader_{};
};

#endif //SANDBOX_OPENGL_22_APPLICATION_IMPLEMENTATION_H_
