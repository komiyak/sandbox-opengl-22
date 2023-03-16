#ifndef SANDBOX_OPENGL_22_BITMAP_FONT_RENDER_H_
#define SANDBOX_OPENGL_22_BITMAP_FONT_RENDER_H_

#include <memory>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <utility>
#include "shader_uniform/font_shader_uniform.h"
#include "vertex_render_object.h"

class Shader;

// ASCII bitmap font をスクリーンに表示するシステム
class BitmapFontRender {
public:
    BitmapFontRender() = default;

    ~BitmapFontRender();

    BitmapFontRender(const BitmapFontRender &) = delete;

    BitmapFontRender &&operator=(const BitmapFontRender &) = delete;

    // 白文字テキスト
    [[maybe_unused]] void RenderWhiteAsciiText(const std::string &ascii_text, int x, int y, int font_size);

    // 黒文字テキスト
    [[maybe_unused]] void RenderBlackAsciiText(const std::string &ascii_text, int x, int y, int font_size);

    // ASCII テキストを任意の位置に描画する
    // param font_size 文字の横幅をピクセルで指定
    // param color 任意の文字色
    void RenderAsciiText(const std::string &ascii_text, int x, int y, int font_size, const glm::vec3 &color);

    // 描画準備のオブジェクト等を生成する
    void Create(
            int screen_width,
            int screen_height,
            int texture_width,
            int texture_height,
            int glyph_width,
            int glyph_height,
            GLint texture_unit_number,
            std::weak_ptr<Shader> shader);

    void Destroy();

private:
    bool created_{};

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

    // ASCII bitmap font の vertex render object
    VertexRenderObject vertex_render_object_{};
    // ASCII bitmap font の shader uniform
    std::shared_ptr<FontShaderUniform> font_shader_uniform_{new FontShaderUniform()};
    // ASCII bitmap font 用のセットアップされたシェーダへのリンク
    std::weak_ptr<Shader> shader_{};
};

#endif //SANDBOX_OPENGL_22_BITMAP_FONT_RENDER_H_
