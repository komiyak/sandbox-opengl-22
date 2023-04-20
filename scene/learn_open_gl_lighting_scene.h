#ifndef SANDBOX_OPENGL_22_LEARN_OPEN_GL_LIGHTING_SCENE_H_
#define SANDBOX_OPENGL_22_LEARN_OPEN_GL_LIGHTING_SCENE_H_

#include <memory>
#include <gl_app/gl.h>
#include <gl_app/scene.h>
#include "../texture.h"
#include "../shader.h"
#include "../vertex_render_object.h"
#include "../shader_uniform/basic_shader_uniform.h"
#include "../shader_uniform/practice_lighting_phong_shading_shader_uniform.h"
#include "../shader_uniform/practice_lighting_lighting_map_shader_uniform.h"


// LearnOpenGL.com の lighting のチャプターを学習するためのシーン
// https://learnopengl.com/Lighting/Colors
class LearnOpenGlLightingScene : public gl_app::Scene {
public:
    void OnFrame() override;

    void OnStart() override;

    void OnDestroy() override;

    void OnKey(int glfw_key, int glfw_action) override;

    static std::shared_ptr<Scene> CreateFactory() {
        return std::shared_ptr<Scene>{new LearnOpenGlLightingScene()};
    }

private:
    float angle_{};
    float light_angle_{};
    float light_strength_{};

    Texture texture_diffuse_map_{};
    Texture texture_specular_map_{};
    Texture texture_emission_map_{};

    std::shared_ptr<Shader> white_vertex_shader_{new Shader()};
    std::shared_ptr<Shader> vertex_color_shader_{new Shader()};
    std::shared_ptr<Shader> sample_lighting_cube_shader_{new Shader()};
    std::shared_ptr<Shader> lighting_map_shader_{new Shader()};

    VertexRenderObject grid_{};
    VertexRenderObject light_source_{};
    VertexRenderObject lighting_target_{};
    VertexRenderObject lighting_map_cube_{};

    std::shared_ptr<BasicShaderUniform> grid_shader_uniform_{new BasicShaderUniform()};
    std::shared_ptr<BasicShaderUniform> light_source_shader_uniform_{new BasicShaderUniform()};
    std::shared_ptr<PracticeLightingPhongShadingShaderUniform> lighting_target_shader_uniform_{
            new PracticeLightingPhongShadingShaderUniform()};
    std::shared_ptr<PracticeLightingLightingMapShaderUniform> lighting_map_shader_uniform_{
            new PracticeLightingLightingMapShaderUniform()};
};

#endif //SANDBOX_OPENGL_22_LEARN_OPEN_GL_LIGHTING_SCENE_H_
