#ifndef SANDBOX_OPENGL_22_SANDBOX_SCENE_H_
#define SANDBOX_OPENGL_22_SANDBOX_SCENE_H_

#include <glad/glad.h>

#include "../application/scene.h"
#include "../texture.h"
#include "../shader.h"

class BasicShaderUniform;

class TextureShaderUniform;

class Texture2dShaderUniform;

class VertexRenderObject;

class BitmapFontRender;

class SandboxScene : public Scene {
public:
    void OnFrame() override;

    void OnStart() override;

    void OnKey(int glfw_key, int glfw_action) override;

    void OnDestroy() override;

    static Scene *CreateFactory() {
        return new SandboxScene();
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

    Shader grid_shader_{};
    Shader shader_{};
    Shader texture_shader_{};
    Shader texture_2d_shader_{};

    BitmapFontRender *up_bitmap_font_render_{};
};

#endif //SANDBOX_OPENGL_22_SANDBOX_SCENE_H_
