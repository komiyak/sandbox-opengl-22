#ifndef SANDBOX_OPENGL_22_LEARN_OPEN_GL_LIGHTING_SCENE_H_
#define SANDBOX_OPENGL_22_LEARN_OPEN_GL_LIGHTING_SCENE_H_

#include "../opengl_glfw.h"
#include "../application/scene.h"
#include "../texture.h"
#include "../shader.h"

class VertexRenderObject;

class BasicShaderUniform;

class PracticeLightingPhongShadingShaderUniform;

class PracticeLightingLightingMapShaderUniform;

// LearnOpenGL.com の lighting のチャプターを学習するためのシーン
// https://learnopengl.com/Lighting/Colors
class LearnOpenGlLightingScene : public Scene {
public:
    void OnFrame() override;

    void OnStart() override;

    void OnDestroy() override;

    void OnKey(int glfw_key, int glfw_action) override;

    static Scene *CreateFactory() {
        return new LearnOpenGlLightingScene();
    }

private:
    float angle_{};
    float light_angle_{};
    float light_strength_{};

    Texture texture_diffuse_map_;
    Texture texture_specular_map_;
    Texture texture_emission_map_;

    Shader white_vertex_shader_{};
    Shader vertex_color_shader_{};
    Shader sample_lighting_cube_shader_{};
    Shader lighting_map_shader_{};

    VertexRenderObject *up_grid_{};
    VertexRenderObject *up_light_source_{};
    VertexRenderObject *up_lighting_target_{};
    VertexRenderObject *up_lighting_map_cube_{};

    BasicShaderUniform *up_grid_shader_uniform_{};
    BasicShaderUniform *up_light_source_shader_uniform_{};
    PracticeLightingPhongShadingShaderUniform *up_lighting_target_shader_uniform_{};
    PracticeLightingLightingMapShaderUniform *up_lighting_map_shader_uniform_{};
};

#endif //SANDBOX_OPENGL_22_LEARN_OPEN_GL_LIGHTING_SCENE_H_
