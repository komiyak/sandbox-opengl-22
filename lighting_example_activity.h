#ifndef SANDBOX_OPENGL_22_LIGHTING_EXAMPLE_ACTIVITY_H_
#define SANDBOX_OPENGL_22_LIGHTING_EXAMPLE_ACTIVITY_H_

#include "application.h"
#include "frame.h"

class Shader;

class VertexRenderObject;

class BasicShaderUniform;

class PracticeLightingPhongShadingShaderUniform;

class LightingExampleActivity : public Application::Activity {
public:
    void OnFrame() override;

    void OnStart() override;

    void OnFrameAfterSwap() override;

    void OnDestroy() override;

    void OnKey(int glfw_key, int glfw_action) override;

    static Application::Activity *CreateActivityFactory() {
        return new LightingExampleActivity();
    }

private:
    float angle_{};
    float light_angle_{};
    Frame frame_{};

    Shader *up_white_vertex_shader_{};
    Shader *up_vertex_color_shader_{};
    Shader *up_sample_lighting_cube_shader_{};

    VertexRenderObject *up_grid_{};
    VertexRenderObject *up_light_source_{};
    VertexRenderObject *up_lighting_target_{};

    BasicShaderUniform *up_grid_shader_uniform_{};
    BasicShaderUniform *up_light_source_shader_uniform_{};
    PracticeLightingPhongShadingShaderUniform *up_lighting_target_shader_uniform_{};
};


#endif //SANDBOX_OPENGL_22_LIGHTING_EXAMPLE_ACTIVITY_H_
