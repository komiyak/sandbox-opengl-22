#ifndef SANDBOX_OPENGL_22_LIGHTING_EXAMPLE_SCENE_H_
#define SANDBOX_OPENGL_22_LIGHTING_EXAMPLE_SCENE_H_

#include <glad/glad.h>

#include "../frame.h"
#include "../application/scene.h"

class Shader;

class VertexRenderObject;

class BasicShaderUniform;

class PracticeLightingPhongShadingShaderUniform;

class PracticeLightingLightingMapShaderUniform;

class LightingExampleScene : public Scene {
public:
    void OnFrame() override;

    void OnStart() override;

    void OnFrameAfterSwap() override;

    void OnDestroy() override;

    void OnKey(int glfw_key, int glfw_action) override;

    static Scene *CreateActivityFactory() {
        return new LightingExampleScene();
    }

private:
    float angle_{};
    float light_angle_{};
    float light_strength_{};
    Frame frame_{};

    GLuint texture_0_{};
    GLuint texture_1_{};
    GLuint texture_2_{};

    Shader *up_white_vertex_shader_{};
    Shader *up_vertex_color_shader_{};
    Shader *up_sample_lighting_cube_shader_{};
    Shader *up_lighting_map_shader_{};

    VertexRenderObject *up_grid_{};
    VertexRenderObject *up_light_source_{};
    VertexRenderObject *up_lighting_target_{};
    VertexRenderObject *up_lighting_map_cube_{};

    BasicShaderUniform *up_grid_shader_uniform_{};
    BasicShaderUniform *up_light_source_shader_uniform_{};
    PracticeLightingPhongShadingShaderUniform *up_lighting_target_shader_uniform_{};
    PracticeLightingLightingMapShaderUniform *up_lighting_map_shader_uniform_{};
};


#endif //SANDBOX_OPENGL_22_LIGHTING_EXAMPLE_SCENE_H_
