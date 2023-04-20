#ifndef SANDBOX_OPENGL_22_SANDBOX_SCENE_H_
#define SANDBOX_OPENGL_22_SANDBOX_SCENE_H_

#include <memory>
#include <gl_app/gl.h>
#include <gl_app/scene.h>

#include "../texture.h"
#include "../shader.h"
#include "../vertex_render_object.h"
#include "../shader_uniform/basic_shader_uniform.h"
#include "../shader_uniform/texture_shader_uniform.h"

class SandboxScene : public gl_app::Scene {
public:
    void OnFrame() override;

    void OnStart() override;

    void OnKey(int glfw_key, int glfw_action) override;

    void OnDestroy() override;

    static std::shared_ptr<Scene> CreateFactory() {
        return std::shared_ptr<Scene>{new SandboxScene()};
    }

private:
    float angle_{0.f};

    Texture texture_grass_{};
    Texture texture_bitmap_font_{};

    std::shared_ptr<BasicShaderUniform> grid_shader_uniform_{new BasicShaderUniform()};
    std::shared_ptr<BasicShaderUniform> axis_shader_uniform_{new BasicShaderUniform()};
    std::shared_ptr<BasicShaderUniform> triangle_shader_uniform_{new BasicShaderUniform()};
    std::shared_ptr<TextureShaderUniform> grass_shader_uniform_{new TextureShaderUniform()};
    std::shared_ptr<BasicShaderUniform> cube_shader_uniform_{new BasicShaderUniform()};

    std::shared_ptr<Shader> grid_shader_{new Shader()};
    std::shared_ptr<Shader> shader_{new Shader()};
    std::shared_ptr<Shader> texture_shader_{new Shader()};
    std::shared_ptr<Shader> texture_2d_shader_{new Shader()};

    VertexRenderObject grid_{};
    VertexRenderObject axis_{};
    VertexRenderObject triangle_{};
    VertexRenderObject grass_{};
    VertexRenderObject cube_{};

};

#endif //SANDBOX_OPENGL_22_SANDBOX_SCENE_H_
