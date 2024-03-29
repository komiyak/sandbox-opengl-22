#ifndef SANDBOX_OPENGL_22_STARTING_SCENE_H_
#define SANDBOX_OPENGL_22_STARTING_SCENE_H_

#include <memory>
#include <gl_app/gl.h>
#include <gl_app/scene.h>
#include "../texture.h"
#include "../bitmap_font_render.h"

#include <gl_app/scene.h>
#include "../shader.h"

// 起動時のナビゲーション等を提供するシーン
class StartingScene : public gl_app::Scene {
public:
    void OnStart() override;

    void OnFrame() override;

    void OnDestroy() override;

    void OnKey(int glfw_key, int glfw_action) override;

    static std::shared_ptr<Scene> Factory() {
        return std::shared_ptr<Scene>{new StartingScene()};
    }

private:
    float count_{};

    Texture texture_{};
    std::shared_ptr<Shader> font_shader_{new Shader()};
    BitmapFontRender bitmap_font_render_{};
};

#endif //SANDBOX_OPENGL_22_STARTING_SCENE_H_
