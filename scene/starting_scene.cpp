#include <gl_app/application.h>
#include <gl_app/debug_util.h>
#include <glm/glm.hpp>

#include "starting_scene.h"
#include "sandbox_scene.h"
#include "learn_open_gl_lighting_scene.h"
#include "learn_open_gl_lighting_light_casters_scene.h"
#include "learn_open_gl_lighting_multiple_lights_scene.h"

void StartingScene::OnStart() {
    font_shader_->BuildFromFile(
            "shader/font.vert",
            "shader/font.frag",
            "outColor");

    texture_.Load(
            "./texture/ascii_bitmap_font.png",
            Texture::ImageFormat::RGBA,
            0);

    // フォント準備
    if (auto application_context = GetApplicationContext().lock()) {
        bitmap_font_render_.Create(
                application_context->GetWindowScreenWidth(),
                application_context->GetWindowScreenHeight(),
                texture_.GetTextureWidth(),
                texture_.GetTextureHeight(),
                4,
                8,
                texture_.GetTextureUnitNumber(),
                font_shader_);
    }
}

void StartingScene::OnFrame() {
    const float min = 0.25;
    const float max = 0.4;
    const float speed = 0.7;

    count_ += GetFrame().GetDeltaTimeF() * speed;
    const float color = (std::sin(count_) + 1.0f) * 0.5f * (max - min) + min;

    glClearColor(color, color, color, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Drawing the title.
    bitmap_font_render_.RenderWhiteAsciiText(
            "THE SANDBOX OF OPENGL",
            40, 40, 38);
    bitmap_font_render_.RenderWhiteAsciiText(
            "Press the key if you need to play that sandbox.",
            40, 120, 14);

    // Drawing the menu.
    bitmap_font_render_.RenderWhiteAsciiText(
            "[ESC] Exit",
            40, 200, 16);
    bitmap_font_render_.RenderWhiteAsciiText(
            "[1] Move to 'SandboxScene'",
            40, 240, 16);
    bitmap_font_render_.RenderWhiteAsciiText(
            "[2] Move to 'LearnOpenGlLightingScene'",
            40, 280, 16);
    bitmap_font_render_.RenderWhiteAsciiText(
            "[3] Move to 'LearnOpenGlLightingLightCastersScene'",
            40, 320, 16);
    bitmap_font_render_.RenderWhiteAsciiText(
            "[4] Move to 'LearnOpenGlLightingMultipleLightsScene'",
            40, 360, 16);
}

void StartingScene::OnDestroy() {
    // 現在の scene の構造上は、scene 切替時に必ず delete される実装なので、on destroy で特別必要な操作はない
}

void StartingScene::OnKey(int glfw_key, int glfw_action) {
    // ESC の場合はとりあえずアプリケーションを終了する
    if (glfw_key == GLFW_KEY_ESCAPE && glfw_action == GLFW_PRESS) {
        SendToDestroy();
    }

    // 任意の Scene を起動する
    if (glfw_key == GLFW_KEY_1 && glfw_action == GLFW_PRESS) {
        LaunchNextScene(SandboxScene::CreateFactory);
    }
    if (glfw_key == GLFW_KEY_2 && glfw_action == GLFW_PRESS) {
        LaunchNextScene(LearnOpenGlLightingScene::CreateFactory);
    }
    if (glfw_key == GLFW_KEY_3 && glfw_action == GLFW_PRESS) {
        LaunchNextScene(LearnOpenGlLightingLightCastersScene::CreateFactory);
    }
    if (glfw_key == GLFW_KEY_4 && glfw_action == GLFW_PRESS) {
        LaunchNextScene(LearnOpenGlLightingMultipleLightsScene::CreateFactory);
    }
}
