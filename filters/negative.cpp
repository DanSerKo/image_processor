#include "negative.h"

Picture Negative::GetPic(const Picture& original) {
    Picture changed = Filter::GetPic(original);
    changed.pixels = new RGB*[changed.dib_header_.height];
    for (size_t i = 0; i < changed.dib_header_.height; i++) {
        changed.pixels[i] = new RGB[changed.dib_header_.width];
        for (size_t j = 0; j < changed.dib_header_.width; j++) {
            changed.pixels[i][j].R = MAX_PIXEL_VALUE - original.pixels[i][j].R;
            changed.pixels[i][j].G = MAX_PIXEL_VALUE - original.pixels[i][j].G;
            changed.pixels[i][j].B = MAX_PIXEL_VALUE - original.pixels[i][j].B;
        }
    }
    return changed;
}

Filter* MakeNegative(const Line& param) {
    if (param.size() != 1) {
        throw std::logic_error("Invalid arguments.");
    }
    if (param[0] != "-neg") {
        throw std::logic_error("Invalid arguments.");
    }
    return new Negative();
}