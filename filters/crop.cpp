#include "crop.h"

Picture Crop::GetPic(const Picture& original) {
    Picture changed = Filter::GetPic(original);
    if (width_ < changed.dib_header_.width) {
        changed.dib_header_.width = width_;
    }
    if (height_ < changed.dib_header_.height) {
        changed.dib_header_.height = height_;
    }
    changed.pixels = new RGB*[changed.dib_header_.height];
    for (size_t i = 0; i < changed.dib_header_.height; i++) {
        int32_t diff = original.dib_header_.height - changed.dib_header_.height;
        changed.pixels[i] = new RGB[changed.dib_header_.width];
        for (size_t j = 0; j < changed.dib_header_.width; j++) {
            changed.pixels[i][j] = original.pixels[i + diff][j];
        }
    }
    return changed;
}

Filter* MakeCrop(const Line& param) {
    if (param.size() != 3) {
        throw std::logic_error("Invalid arguments.");
    }
    if (param[0] != "-crop") {
        throw std::logic_error("Invalid arguments.");
    }
    int32_t width = -1;
    int32_t height = -1;
    try {
        width = stoi(param[1]);
        height = stoi(param[2]);
    } catch (std::exception& e) {
        throw std::logic_error("Invalid arguments");
    }
    if (width <= 0 || height <= 0) {
        throw std::logic_error("Invalid arguments.");
    }
    return new Crop(width, height);
}
