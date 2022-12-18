#include <cstring>

#include "bitmap_font_render.h"
#include "debug.h"
#include "vertex_render_object.h"
#include "game_data.h"
#include "vertex_specification/texture_2d_vertex_specification.h"
#include "shader.h"
#include "game_math.h"

void BitmapFontRender::Initialize() {
    up_vertex_render_object_ = new VertexRenderObject();
    up_vertex_render_object_->Initialize(
            sizeof(GameData::kQuad2dPivotTopLeftVertices),
            (void *) GameData::kQuad2dPivotTopLeftVertices,
            Texture2dVertexSpecification{
                    p_shader_->GetAttribVariableLocation("position"),
                    p_shader_->GetAttribVariableLocation("texcoord")},
            p_shader_,
            &font_shader_uniform_,
            GL_STATIC_DRAW,
            GL_TRIANGLE_STRIP,
            4);
}

void BitmapFontRender::Finalize() {
    FINALIZE_AND_DELETE(up_vertex_render_object_);
    p_shader_ = nullptr;
}

[[maybe_unused]] void BitmapFontRender::RenderWhiteAsciiText(const char *ascii_text, int x, int y, int font_size) {
    RenderAsciiText(ascii_text, x, y, font_size, glm::vec3(1, 1, 1));
}

[[maybe_unused]] void BitmapFontRender::RenderBlackAsciiText(const char *ascii_text, int x, int y, int font_size) {
    RenderAsciiText(ascii_text, x, y, font_size, glm::vec3(0, 0, 0));
}

void BitmapFontRender::RenderAsciiText(const char *ascii_text, int x, int y, int font_size, const glm::vec3 &color) {
    DEBUG_ASSERT(up_vertex_render_object_);
    DEBUG_ASSERT(font_size > 0);
    if (!up_vertex_render_object_) return;

    const int row_max = 16; // テクスチャの横方向の分割数
    const int column_max = 8; // テクスチャの縦方向の分割数

    font_shader_uniform_.SetTextureUnit(texture_unit_number_);

    for (int i = 0; i < std::strlen(ascii_text); i++) {
        const char c = ascii_text[i];
        const int row = c % 0x10; // 縦方向の位置
        const int column = c / 0x10; // 縦方向の位置

        // テクスチャ座標系で該当する文字が存在する場所を特定する
        const int s_begin = ((texture_width_ / row_max) * row);
        const int t_begin = ((texture_height_ / column_max) * column);
        // texcoord に変換
        const float texcoord_s_begin = glm::clamp((float) s_begin / (float) texture_width_, 0.0f, 1.0f);
        const float texcoord_t_begin = glm::clamp((float) t_begin / (float) texture_height_, 0.0f, 1.0f);
        // テクスチャ座標系のスケール値
        const float scale_x = glm::clamp(1.0f / row_max, 0.0f, 1.0f);
        const float scale_y = glm::clamp(1.0f / column_max, 0.0f, 1.0f);

        // 描画時の大きさをピクセルで指定
        const int font_size_w = font_size;
        const int font_size_h = (glyph_height_ / glyph_width_) * font_size;

        font_shader_uniform_.SetTranslation(
                game_math::TransformFromScreenCoordinateToDeviceCoordinate(
                        x + (font_size_w * i), y, screen_width_, screen_height_));
        font_shader_uniform_.SetScaling(
                glm::vec2(
                        (float) font_size_w / (float) screen_width_ * 2.f,
                        (float) font_size_h / (float) screen_height_ * 2.f));
        font_shader_uniform_.SetTexcoordTranslation(glm::vec2(texcoord_s_begin, texcoord_t_begin));
        font_shader_uniform_.SetTexcoordScaling(glm::vec2(scale_x, scale_y));
        font_shader_uniform_.SetColor(glm::vec3(color.x, color.y, color.z));

        up_vertex_render_object_->Render();
    }
}
