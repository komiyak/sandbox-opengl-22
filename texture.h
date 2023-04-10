#ifndef SANDBOX_OPENGL_22_TEXTURE_H_
#define SANDBOX_OPENGL_22_TEXTURE_H_

#include <string>
#include "opengl_glfw.h"

// 簡単な Texture 管理クラス
class Texture {
public:
    constexpr static GLint ERROR_TEXTURE_UNIT_NUMBER = -1;

    enum ImageFormat {
        RGB,
        RGBA
    };

    Texture() = default;

    ~Texture();

    Texture(const Texture &) = delete;

    Texture &operator=(const Texture &) = delete;

    // テクスチャファイルをロードし GPU に転送する
    void Load(const std::string& file_path, ImageFormat image_format, GLint texture_unit_number);

    // テクスチャをアンロードする
    void Unload();

    [[maybe_unused]] [[nodiscard]] GLint GetTextureUnitNumber() const {
        return loaded_ ? texture_unit_number_ : ERROR_TEXTURE_UNIT_NUMBER;
    }

    [[maybe_unused]] [[nodiscard]] int GetTextureWidth() const {
        return texture_width_;
    }

    [[maybe_unused]] [[nodiscard]] int GetTextureHeight() const {
        return texture_height_;
    }

private:
    static GLuint GetPngFormat(ImageFormat image_format);

    static GLint GetGlTextureFormat(ImageFormat image_format);

    static GLuint GetGlTextureNumber(GLint texture_unit_number);

    // load 済みならば true
    bool loaded_{};

    GLuint texture_{};
    GLint texture_unit_number_{};

    int texture_width_{};
    int texture_height_{};
};

#endif //SANDBOX_OPENGL_22_TEXTURE_H_
