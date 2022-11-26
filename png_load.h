#ifndef SANDBOX_OPENGL_22_PNG_LOAD_H
#define SANDBOX_OPENGL_22_PNG_LOAD_H

#include <png.h>

#include "base_object.h"

// libpng を利用した png ファイル管理クラス
class PngLoad : public BaseObject {
public:
    // png file ロード
    // params p_file_name 画像ファイルパス
    // params format 画像ファイルフォーマット (PNG_FORMAT_RGB, PNG_FORMAT_RGBA ... from libpng)
    void LoadFile(const char *p_file_name, png_uint_32 format);

    // png file ロード解除
    void Unload();

    // 読み込んだバイナリデータを返却
    const void *GetData() {
        return png_bytep_;
    }

    struct ImageSize {
        int width;
        int height;
    };

    [[nodiscard]] ImageSize GetImageSize() const {
        ImageSize image_size{};
        image_size.width = (int) png_image_.width;
        image_size.height = (int) png_image_.height;
        return image_size;
    }

    void Finalize() override {
        Unload();
    }

private:
    void Initialize(png_uint_32 version);

    // Already loaded an image.
    bool loaded_{};
    // libpng
    png_image png_image_{};
    // libpng
    png_bytep png_bytep_{};
};

#endif //SANDBOX_OPENGL_22_PNG_LOAD_H
