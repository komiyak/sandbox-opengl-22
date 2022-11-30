#ifndef SANDBOX_OPENGL_22_MAIN_ACTIVITY_H_
#define SANDBOX_OPENGL_22_MAIN_ACTIVITY_H_

#include "application.h"

class Shader;

class BitmapFontRender;

class MainActivity : public Application::Activity {
public:
    void OnStart() override;

    void OnFrame() override;

    void OnDestroy() override;

    void OnKey(int glfw_key, int glfw_action) override;

private:
    GLuint texture_0_{};
    Shader *up_font_shader_{};
    BitmapFontRender *up_bitmap_font_render_;
};

#endif //SANDBOX_OPENGL_22_MAIN_ACTIVITY_H_
