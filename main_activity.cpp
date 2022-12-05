#include <glm/glm.hpp>
#include "main_activity.h"
#include "opengl_debug.h"
#include "shader.h"
#include "png_load.h"
#include "bitmap_font_render.h"
#include "basic_sample_activity.h"
#include "lighting_example_activity.h"
#include "shader_data.h"

void MainActivity::OnStart() {

    up_font_shader_ = new Shader();
    up_font_shader_->BuildFromFile(
            "shader/font.vert",
            "shader/font.frag",
            shader_data::kAttribVariableLocationsOfFontShader,
            shader_data::kAttribVariableLocationsOfFontShaderSize,
            shader_data::kUniformVariableLocationsOfFontShader,
            shader_data::kUniformVariableLocationsOfFontShaderSize);

    // bitmap font texture (texture unit = 1)
    glGenTextures(1, &texture_0_);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture_0_);

    PngLoad png_load{};
    png_load.LoadFile("./texture/ascii_bitmap_font.png", PNG_FORMAT_RGBA);
    glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            png_load.GetImageSize().width,
            png_load.GetImageSize().height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            png_load.GetData());
    OPENGL_DEBUG_CHECK();

    // フォント準備
    up_bitmap_font_render_ = new BitmapFontRender(
            p_context_->GetWindowScreenWidth(),
            p_context_->GetWindowScreenHeight(),
            png_load.GetImageSize().width,
            png_load.GetImageSize().height,
            4,
            8,
            up_font_shader_->GetUniformVariableLocation("tex"),
            up_font_shader_->GetUniformVariableLocation("color"),
            up_font_shader_->GetUniformVariableLocation("translation_vec"),
            up_font_shader_->GetUniformVariableLocation("scaling_vec"),
            up_font_shader_->GetUniformVariableLocation("texcoord_translation_vec"),
            up_font_shader_->GetUniformVariableLocation("texcoord_scaling_vec"),
            up_font_shader_);
    up_bitmap_font_render_->Initialize();
    png_load.Finalize();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NullDereference"

void MainActivity::OnFrame() {
    frame_.StartFrame();

    const float min = 0.25;
    const float max = 0.4;
    const float speed = 0.7;

    count_ += frame_.GetDeltaTimeF() * speed;
    const float color = (std::sin(count_) + 1.0f) * 0.5f * (max - min) + min;

    glClearColor(color, color, color, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
            "[1] Move to 'BasicSampleActivity'",
            40, 240, 16);
    up_bitmap_font_render_->RenderWhiteAsciiText(
            "[2] Move to 'LightingExampleActivity'",
            40, 280, 16);
}

#pragma clang diagnostic pop

void MainActivity::OnDestroy() {
    frame_.Finalize();
    glDeleteTextures(1, &texture_0_);
    FINALIZE_AND_DELETE(up_font_shader_);
    FINALIZE_AND_DELETE(up_bitmap_font_render_);
}

void MainActivity::OnKey(int glfw_key, int glfw_action) {
    // ESC の場合はとりあえずアプリケーションを終了する
    if (glfw_key == GLFW_KEY_ESCAPE && glfw_action == GLFW_PRESS) {
        should_destroy_ = true;
    }

    // 任意の Activity を起動する
    if (glfw_key == GLFW_KEY_1 && glfw_action == GLFW_PRESS) {
        should_destroy_ = true;
        next_activity_ = BasicSampleActivity::CreateActivityFactory;
    }
    if (glfw_key == GLFW_KEY_2 && glfw_action == GLFW_PRESS) {
        should_destroy_ = true;
        next_activity_ = LightingExampleActivity::CreateActivityFactory;
    }
}

void MainActivity::OnFrameAfterSwap() {
    frame_.EndFrame();
}
