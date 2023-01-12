#ifndef SANDBOX_OPENGL_22_LEARN_OPEN_GL_LIGHTING_MULTIPLE_LIGHTS_SCENE_H_
#define SANDBOX_OPENGL_22_LEARN_OPEN_GL_LIGHTING_MULTIPLE_LIGHTS_SCENE_H_

#include "../opengl_glfw.h"
#include "../application/scene.h"
#include "../shader.h"
#include "../texture.h"
#include "../vertex_render_object.h"
#include "../shader_uniform/basic_shader_uniform.h"

// LearnOpenGL.com の lighting / Multiple lights の学習用のシーン
// https://learnopengl.com/Lighting/Multiple-lights
class LearnOpenGlLightingMultipleLightsScene : public Scene {
public:
    void OnStart() override;

    void OnFrame() override;

    void OnDestroy() override;

    void OnKey(int glfw_key, int glfw_action) override;

    static Scene *CreateFactory() {
        return new LearnOpenGlLightingMultipleLightsScene();
    }
private:
    // 頂点カラー shader
    Shader vertex_color_shader_;
    // multiple lights shader
    Shader multiple_lights_shader_;

    // コンテナ用 diffuse map
    Texture container_texture_;
    // コンテナ用 specular map
    Texture container_specular_map_texture_;

    // コンテナオブジェクト
    VertexRenderObject container_;
    // 原点用の３軸表示
    VertexRenderObject axis_;

    // 原点用の３軸用の shader uniform
    BasicShaderUniform axis_shader_uniform_;
};


#endif //SANDBOX_OPENGL_22_LEARN_OPEN_GL_LIGHTING_MULTIPLE_LIGHTS_SCENE_H_
