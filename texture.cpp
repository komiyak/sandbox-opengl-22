#include <iostream>

#include "texture.h"
#include "debug.h"
#include "opengl_debug.h"
#include "png_load.h"

void Texture::Load(const std::string& file_path, Texture::ImageFormat image_format, GLint texture_unit_number) {
    if (loaded_) return;

    glGenTextures(1, &texture_);
    glActiveTexture(GetGlTextureNumber(texture_unit_number));
    texture_unit_number_ = texture_unit_number;
    glBindTexture(GL_TEXTURE_2D, texture_);

    PngLoad png_load{};
    png_load.LoadFile(file_path, GetPngFormat(image_format));
    glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GetGlTextureFormat(image_format),
            png_load.GetImageSize().width,
            png_load.GetImageSize().height,
            0,
            GetGlTextureFormat(image_format),
            GL_UNSIGNED_BYTE,
            png_load.GetData());
    texture_width_ = png_load.GetImageSize().width;
    texture_height_ = png_load.GetImageSize().height;
    png_load.Unload(); // texture 転送後は不要なのですぐに削除する
    OPENGL_DEBUG_CHECK();

    // Note: この設定は将来的には柔軟に行えるようにしたい
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    OPENGL_DEBUG_CHECK();

    loaded_ = true;
}

void Texture::Unload() {
    if (loaded_) {
        glDeleteTextures(1, &texture_);
    }
    loaded_ = false;
}

GLuint Texture::GetPngFormat(Texture::ImageFormat image_format) {
    switch (image_format) {
        case RGB:
            return PNG_FORMAT_RGB;
        case RGBA:
            return PNG_FORMAT_RGBA;
        default:
            DEBUG_ABORT_MESSAGE("Not implemented");
    }
}

GLint Texture::GetGlTextureFormat(Texture::ImageFormat image_format) {
    switch (image_format) {
        case RGB:
            return GL_RGB;
        case RGBA:
            return GL_RGBA;
        default:
            DEBUG_ABORT_MESSAGE("Not implemented");
    }
}

GLuint Texture::GetGlTextureNumber(GLint texture_unit_number) {
    // 面倒なので定義は途中まで
    switch (texture_unit_number) {
        case 0:
            return GL_TEXTURE0;
        case 1:
            return GL_TEXTURE1;
        case 2:
            return GL_TEXTURE2;
        case 3:
            return GL_TEXTURE3;
        case 4:
            return GL_TEXTURE4;
        case 5:
            return GL_TEXTURE5;
        case 6:
            return GL_TEXTURE6;
        case 7:
            return GL_TEXTURE7;
        case 8:
            return GL_TEXTURE8;
        case 9:
            return GL_TEXTURE9;
        case 10:
            return GL_TEXTURE10;
        default:
            DEBUG_ABORT_MESSAGE("Not implemented");
    }
}

Texture::~Texture() {
    try {
        Unload();
    } catch (...) {
        std::cerr << "(Texture) Fatal error in destructor." << std::endl;
    }
}
