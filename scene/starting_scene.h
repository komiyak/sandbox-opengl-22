#ifndef SANDBOX_OPENGL_22_STARTING_SCENE_H_
#define SANDBOX_OPENGL_22_STARTING_SCENE_H_

#include <glad/glad.h>

#include "../frame.h"
#include "../application/scene.h"

class Shader;

class BitmapFontRender;

// 起動時のナビゲーション等を提供するシーン
class StartingScene : public Scene {
public:
    void OnStart() override;

    void OnFrame() override;

    void OnFrameAfterSwap() override;

    void OnDestroy() override;

    void OnKey(int glfw_key, int glfw_action) override;

private:
    Frame frame_{};
    float count_{};

    GLuint texture_0_{};
    Shader *up_font_shader_{};
    BitmapFontRender *up_bitmap_font_render_{};
};

#endif //SANDBOX_OPENGL_22_STARTING_SCENE_H_
