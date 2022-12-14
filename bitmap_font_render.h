#ifndef SANDBOX_OPENGL_22_BITMAP_FONT_RENDER_H_
#define SANDBOX_OPENGL_22_BITMAP_FONT_RENDER_H_

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "base_object.h"
#include "font_shader_uniform.h"

class VertexRenderObject;

class Shader;

// ASCII bitmap font をスクリーンに表示するシステム
class BitmapFontRender : public BaseObject {
public:
    BitmapFontRender(
            int screen_width,
            int screen_height,
            int texture_width,
            int texture_height,
            int glyph_width,
            int glyph_height,
            GLint texture_unit_number,
            GLint uniform_texture_unit,
            GLint uniform_color,
            GLint uniform_translation_vec,
            GLint uniform_scaling_vec,
            GLint uniform_texcoord_translation_vec,
            GLint uniform_texcoord_scaling_vec,
            Shader *p_shader)
            : screen_width_(screen_width),
              screen_height_(screen_height),
              texture_width_(texture_width),
              texture_height_(texture_height),
              glyph_width_(glyph_width),
              glyph_height_(glyph_height),
              texture_unit_number_(texture_unit_number),
              font_shader_uniform_(
                      uniform_texture_unit,
                      uniform_color,
                      uniform_translation_vec,
                      uniform_scaling_vec,
                      uniform_texcoord_translation_vec,
                      uniform_texcoord_scaling_vec),
              p_shader_(p_shader) {}

    // 白文字テキスト
    [[maybe_unused]] void RenderWhiteAsciiText(const char *ascii_text, int x, int y, int font_size);

    // 黒文字テキスト
    [[maybe_unused]] void RenderBlackAsciiText(const char *ascii_text, int x, int y, int font_size);

    // ASCII テキストを任意の位置に描画する
    // param font_size 文字の横幅をピクセルで指定
    // param color 任意の文字色
    void RenderAsciiText(const char *ascii_text, int x, int y, int font_size, const glm::vec3 &color);

    void Initialize();

    void Finalize() override;

private:
    // スクリーンの横幅
    int screen_width_{};
    // スクリーンの縦幅
    int screen_height_{};
    // ASCII bitmap font のテクスチャ横幅
    int texture_width_{};
    // ASCII bitmap font のテクスチャ縦幅
    int texture_height_{};
    // ASCII bitmap font の glyph 横幅
    int glyph_width_{};
    // ASCII bitmap font の glyph 縦幅
    int glyph_height_{};
    // ASCII bitmap font の texture unit
    GLint texture_unit_number_{};

    // ASCII bitmap font の shader uniform
    FontShaderUniform font_shader_uniform_;
    // ASCII bitmap font の vertex render object
    VertexRenderObject *up_vertex_render_object_{};
    // ASCII bitmap font 用のセットアップされたシェーダへのリンク
    Shader *p_shader_{};
};

#endif //SANDBOX_OPENGL_22_BITMAP_FONT_RENDER_H_
