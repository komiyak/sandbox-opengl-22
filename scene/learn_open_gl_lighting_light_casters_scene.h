#ifndef SANDBOX_OPENGL_22_LEARN_OPEN_GL_LIGHTING_LIGHT_CASTERS_SCENE_H_
#define SANDBOX_OPENGL_22_LEARN_OPEN_GL_LIGHTING_LIGHT_CASTERS_SCENE_H_

#include "../opengl_glfw.h"
#include "../application/scene.h"
#include "../shader.h"
#include "../texture.h"
#include "../vertex_render_object.h"
#include "../learnopengl_lighting_directional_light_shader_uniform.h"

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
    // コンテナ用 shader
    Shader container_shader_;
    // 頂点カラー shader
    Shader vertex_color_shader_;

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
};


#endif //SANDBOX_OPENGL_22_LEARN_OPEN_GL_LIGHTING_LIGHT_CASTERS_SCENE_H_
