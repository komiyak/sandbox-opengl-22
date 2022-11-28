#ifndef SANDBOX_OPENGL_22_MAIN_APPLICATION_H_
#define SANDBOX_OPENGL_22_MAIN_APPLICATION_H_

#include "application.h"
#include "frame.h"

class BasicShaderUniform;

class TextureShaderUniform;

class VertexRenderObject;

class Shader;

class MainApplication : public Application::Content {
public:
    void OnFrame() override;

    void OnFrameAfterSwap() override;

    void OnStart() override;

    void OnDestroy() override;

private:
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

#endif //SANDBOX_OPENGL_22_MAIN_APPLICATION_H_