#include <cstring>
#include <cstdlib>

#include "png_load.h"

void PngLoad::LoadFile(const char *p_file_name, png_uint_32 format) {
    if (!p_file_name) return;
    if (loaded_) return;

    Initialize(PNG_IMAGE_VERSION);

    if (png_image_begin_read_from_file(&(png_image_), p_file_name)) {
        png_image_.format = format;
        png_bytep_ = static_cast<png_bytep>(malloc(PNG_IMAGE_SIZE(png_image_)));

        if (png_image_finish_read(&png_image_, nullptr, png_bytep_, 0, nullptr)) {
            loaded_ = true;
            return; // Successful
        } else {
            fprintf(stderr, "Error png_load.");
            fflush(stderr);
        }
    }
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantParameter"

void PngLoad::Initialize(png_uint_32 version) {
    memset(&png_image_, 0, sizeof(png_image_));
    png_image_.version = version;
}

#pragma clang diagnostic pop

void PngLoad::Unload() {
    if (!loaded_) return;

    if (png_bytep_) {
        free(png_bytep_);
        png_bytep_ = nullptr;
    } else {
        png_image_free(&png_image_);
    }
    loaded_ = false;
}
