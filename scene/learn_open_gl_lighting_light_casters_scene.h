#ifndef SANDBOX_OPENGL_22_LEARN_OPEN_GL_LIGHTING_LIGHT_CASTERS_SCENE_H_
#define SANDBOX_OPENGL_22_LEARN_OPEN_GL_LIGHTING_LIGHT_CASTERS_SCENE_H_

#include "../opengl_glfw.h"
#include "../application/scene.h"
#include "../shader.h"
#include "../texture.h"
#include "../vertex_render_object.h"
#include "../shader_uniform/learnopengl_lighting_directional_light_shader_uniform.h"
#include "../shader_uniform/learnopengl_lighting_point_light_shader_uniform.h"
#include "../shader_uniform/basic_shader_uniform.h"

class BitmapFontRender;

// LearnOpenGL.com の lighting / light casters の学習用のシーン
// https://learnopengl.com/Lighting/Light-casters
class LearnOpenGlLightingLightCastersScene : public Scene {
public:
    void OnStart() override;

    void OnFrame() override;

    void OnDestroy() override;

    void OnKey(int glfw_key, int glfw_action) override;

    static Scene *CreateFactory() {
        return new LearnOpenGlLightingLightCastersScene();
    }

private:
    enum Mode {
        kDirectionalLight,
        kPointLight,
        kSpotlight
    };
    enum DirectionalLightMode {
        kDirectionalLightA,
        kDirectionalLightB,
        kDirectionalLightC,
    };

    float angle_{};
    float point_light_position_x_{};

    // 動作モード
    Mode mode_{kDirectionalLight};
    // Directional light mode のときのサブモード
    DirectionalLightMode directional_light_mode_{kDirectionalLightA};

    // コンテナ用 shader (For directional light)
    Shader container_shader_;
    // コンテナ用 shader (For point light)
    Shader container_point_light_shader_;
    // 頂点カラー shader
    Shader vertex_color_shader_;
    // Font 用 shader
    Shader font_shader_;

    // Bitmap font 用 texture
    Texture font_texture_;
    // コンテナ用 diffuse map
    Texture container_texture_;
    // コンテナ用 specular map
    Texture container_specular_map_texture_;

    // コンテナオブジェクト
    VertexRenderObject container_;
    // 原点用の３軸表示
    VertexRenderObject axis_;

    // コンテナ用 shader uniform
    LearnopenglLightingDirectionalLightShaderUniform container_shader_uniform_;
    // コンテナ用 (For point light) shader uniform
    LearnopenglLightingPointLightShaderUniform container_point_light_shader_uniform_;
    // 原点用の３軸用の shader uniform
    BasicShaderUniform axis_shader_uniform_;

    // Bitmap font
    BitmapFontRender *up_bitmap_font_render_{};
};


#endif //SANDBOX_OPENGL_22_LEARN_OPEN_GL_LIGHTING_LIGHT_CASTERS_SCENE_H_
