#include <glm/glm.hpp>

#include "starting_scene.h"
#include "../application/application.h"
#include "../opengl_debug.h"
#include "../shader.h"
#include "../bitmap_font_render.h"
#include "sandbox_scene.h"
#include "learn_open_gl_lighting_scene.h"
#include "learn_open_gl_lighting_light_casters_scene.h"

void StartingScene::OnStart() {
    up_font_shader_ = new Shader();
    up_font_shader_->BuildFromFile(
            "shader/font.vert",
            "shader/font.frag");

    texture_.Load(
            "./texture/ascii_bitmap_font.png",
            Texture::ImageFormat::RGBA,
            0);

    // フォント準備
    up_bitmap_font_render_ = new BitmapFontRender(
            p_application_context_->GetWindowScreenWidth(),
            p_application_context_->GetWindowScreenHeight(),
            texture_.GetTextureWidth(),
            texture_.GetTextureHeight(),
            4,
            8,
            texture_.GetTextureUnitNumber(),
            up_font_shader_->GetUniformVariableLocation("tex"),
            up_font_shader_->GetUniformVariableLocation("color"),
            up_font_shader_->GetUniformVariableLocation("translation_vec"),
            up_font_shader_->GetUniformVariableLocation("scaling_vec"),
            up_font_shader_->GetUniformVariableLocation("texcoord_translation_vec"),
            up_font_shader_->GetUniformVariableLocation("texcoord_scaling_vec"),
            up_font_shader_);

    up_bitmap_font_render_->Initialize();
}

void StartingScene::OnFrame() {
    const float min = 0.25;
    const float max = 0.4;
    const float speed = 0.7;

    count_ += GetFrame().GetDeltaTimeF() * speed;
    const float color = (std::sin(count_) + 1.0f) * 0.5f * (max - min) + min;

    glClearColor(color, color, color, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (up_bitmap_font_render_) {
        // Drawing the title.
        up_bitmap_font_render_->RenderWhiteAsciiText(
                "THE SANDBOX OF OPENGL",
                40, 40, 38);
        up_bitmap_font_render_->RenderWhiteAsciiText(
                "Press the key if you need to play that sandbox.",
                40, 120, 14);

        // Drawing the menu.
        up_bitmap_font_render_->RenderWhiteAsciiText(
                "[ESC] Exit",
                40, 200, 16);
        up_bitmap_font_render_->RenderWhiteAsciiText(
                "[1] Move to 'SandboxScene'",
                40, 240, 16);
        up_bitmap_font_render_->RenderWhiteAsciiText(
                "[2] Move to 'LearnOpenGlLightingScene'",
                40, 280, 16);
        up_bitmap_font_render_->RenderWhiteAsciiText(
                "[3] Move to 'LearnOpenGlLightingLightCastersScene'",
                40, 320, 16);
    }
}

void StartingScene::OnDestroy() {
    texture_.Finalize();
    FINALIZE_AND_DELETE(up_font_shader_);
    FINALIZE_AND_DELETE(up_bitmap_font_render_);
}

void StartingScene::OnKey(int glfw_key, int glfw_action) {
    // ESC の場合はとりあえずアプリケーションを終了する
    if (glfw_key == GLFW_KEY_ESCAPE && glfw_action == GLFW_PRESS) {
        should_destroy_ = true;
    }

    // 任意の Scene を起動する
    if (glfw_key == GLFW_KEY_1 && glfw_action == GLFW_PRESS) {
        should_destroy_ = true;
        next_scene_ = SandboxScene::CreateFactory;
    }
    if (glfw_key == GLFW_KEY_2 && glfw_action == GLFW_PRESS) {
        should_destroy_ = true;
        next_scene_ = LearnOpenGlLightingScene::CreateFactory;
    }
    if (glfw_key == GLFW_KEY_3 && glfw_action == GLFW_PRESS) {
        should_destroy_ = true;
        next_scene_ = LearnOpenGlLightingLightCastersScene::CreateFactory;
    }
}
