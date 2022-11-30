#include "main_activity.h"
#include "opengl_debug.h"
#include "shader.h"
#include "png_load.h"
#include "bitmap_font_render.h"

void MainActivity::OnStart() {
    up_font_shader_ = new Shader();
    up_font_shader_->BuildFromFile("shader/texture_2d.vert", "shader/texture_2d.frag");


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
            up_font_shader_->GetTextureUnitUniformLocation(),
            up_font_shader_->GetTranslationVecUniformLocation(),
            up_font_shader_->GetScalingVecUniformLocation(),
            up_font_shader_->GetTexcoordTranslationVecUniformLocation(),
            up_font_shader_->GetTexcoordScalingVecUniformLocation(),
            up_font_shader_);
    up_bitmap_font_render_->Initialize();
    png_load.Finalize();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void MainActivity::OnFrame() {
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Drawing the title.
    up_bitmap_font_render_->RenderAsciiText(
            "THE SANDBOX OF OPENGL",
            40, 40, 38);
    up_bitmap_font_render_->RenderAsciiText(
            "Press the key that if you need to play a sandbox.",
            40, 120, 14);

    // Drawing the menu.
    up_bitmap_font_render_->RenderAsciiText(
            "[ESC] Exit",
            40, 200, 18);
    up_bitmap_font_render_->RenderAsciiText(
            "[1] Move to 'BasicSampleActivity'",
            40, 240, 18);
}

void MainActivity::OnDestroy() {
    glDeleteTextures(1, &texture_0_);
    FINALIZE_AND_DELETE(up_font_shader_);
    FINALIZE_AND_DELETE(up_bitmap_font_render_);
}

void MainActivity::OnKey(int glfw_key, int glfw_action) {
    // ESC の場合はとりあえずアプリケーションを終了する
    if (glfw_key == GLFW_KEY_ESCAPE && glfw_action == GLFW_PRESS) {
        should_destroy_ = true;
    }
}
