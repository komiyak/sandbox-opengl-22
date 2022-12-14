#ifndef SANDBOX_OPENGL_22_SAMPLE_SCENE_H_
#define SANDBOX_OPENGL_22_SAMPLE_SCENE_H_

#include <glad/glad.h>

#include "../application_scene/scene.h"
#include "../texture.h"

class BasicShaderUniform;

class TextureShaderUniform;

class Texture2dShaderUniform;

class VertexRenderObject;

class Shader;

class BitmapFontRender;

class SampleActivity : public Scene {
public:
    void OnFrame() override;

    void OnStart() override;

    void OnKey(int glfw_key, int glfw_action) override;

    void OnDestroy() override;

    static Scene *CreateActivityFactory() {
        return new SampleActivity();
    }

private:
    float angle_{0.f};

    Texture texture_grass_;
    Texture texture_bitmap_font_;

    BasicShaderUniform *up_grid_shader_uniform_{};
    BasicShaderUniform *up_axis_shader_uniform_{};
    BasicShaderUniform *up_triangle_shader_uniform_{};
    TextureShaderUniform *up_grass_shader_uniform_{};
    BasicShaderUniform *up_cube_shader_uniform_{};

    VertexRenderObject *up_grid_{};
    VertexRenderObject *up_axis_{};
    VertexRenderObject *up_triangle_{};
    VertexRenderObject *up_grass_{};
    VertexRenderObject *up_cube_{};

    Shader *up_grid_shader_{};
    Shader *up_shader_{};
    Shader *up_texture_shader_{};
    Shader *up_texture_2d_shader_{};

    BitmapFontRender *up_bitmap_font_render_{};
};

#endif //SANDBOX_OPENGL_22_SAMPLE_SCENE_H_
