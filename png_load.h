//
// Created by komiyak on 22/10/10.
//

#ifndef OPENGL_3_2_TUTORIAL_PNG_LOAD_H
#define OPENGL_3_2_TUTORIAL_PNG_LOAD_H

#include <png.h>

class PngLoad {
public:
    // png file ロード
    void LoadFile(const char *p_file_name);

    // png file ロード解除
    void Unload();

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

private:
    void Initialize(png_uint_32 version);

    // libpng
    png_image png_image_;
    // libpng
    png_bytep png_bytep_;
};


#endif //OPENGL_3_2_TUTORIAL_PNG_LOAD_H
