#ifndef SANDBOX_OPENGL_22_LEARN_OPEN_GL_LIGHTING_LIGHT_CASTERS_SCENE_H_
#define SANDBOX_OPENGL_22_LEARN_OPEN_GL_LIGHTING_LIGHT_CASTERS_SCENE_H_

#include <memory>
#include "../opengl_glfw.h"
#include "../application/scene.h"
#include "../shader.h"
#include "../texture.h"
#include "../vertex_render_object.h"
#include "../bitmap_font_render.h"
#include "../shader_uniform/learnopengl_lighting_directional_light_shader_uniform.h"
#include "../shader_uniform/learnopengl_lighting_point_light_shader_uniform.h"
#include "../shader_uniform/learnopengl_lighting_spotlight_shader_uniform.h"
#include "../shader_uniform/basic_shader_uniform.h"

// LearnOpenGL.com の lighting / light casters の学習用のシーン
// https://learnopengl.com/Lighting/Light-casters
class LearnOpenGlLightingLightCastersScene : public Scene {
public:
    void OnStart() override;

    void OnFrame() override;

    void OnDestroy() override;

    void OnKey(int glfw_key, int glfw_action) override;

    static std::shared_ptr<Scene> CreateFactory() {
        return std::shared_ptr<Scene>{new LearnOpenGlLightingLightCastersScene()};
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
    std::shared_ptr<Shader> container_shader_{new Shader};
    // コンテナ用 shader (For point light)
    std::shared_ptr<Shader> container_point_light_shader_{new Shader};
    // コンテナ用 shader (For spotlight)
    std::shared_ptr<Shader> container_spotlight_shader_{new Shader};
    // 頂点カラー shader
    std::shared_ptr<Shader> vertex_color_shader_{new Shader};
    // Font 用 shader
    std::shared_ptr<Shader> font_shader_{new Shader};

    // Bitmap font 用 texture
    Texture font_texture_{};
    // コンテナ用 diffuse map
    Texture container_texture_{};
    // コンテナ用 specular map
    Texture container_specular_map_texture_{};

    // コンテナオブジェクト
    VertexRenderObject container_{};
    // 原点用の３軸表示
    VertexRenderObject axis_{};

    // コンテナ用 shader uniform
    std::shared_ptr<LearnopenglLightingDirectionalLightShaderUniform> container_shader_uniform_{
            new LearnopenglLightingDirectionalLightShaderUniform};
    // コンテナ用 (For point light) shader uniform
    std::shared_ptr<LearnopenglLightingPointLightShaderUniform> container_point_light_shader_uniform_{
            new LearnopenglLightingPointLightShaderUniform};
    // コンテナ用 (For spotlight) shader uniform
    std::shared_ptr<LearnopenglLightingSpotlightShaderUniform> container_spotlight_shader_uniform_{
            new LearnopenglLightingSpotlightShaderUniform};
    // 原点用の３軸用の shader uniform
    std::shared_ptr<BasicShaderUniform> axis_shader_uniform_{new BasicShaderUniform};

    // Bitmap font
    BitmapFontRender bitmap_font_render_{};
};


#endif //SANDBOX_OPENGL_22_LEARN_OPEN_GL_LIGHTING_LIGHT_CASTERS_SCENE_H_
