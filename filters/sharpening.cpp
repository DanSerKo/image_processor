#include "sharpening.h"

Picture Sharpening::GetPic(const Picture& original) {
    Picture changed = Filter::GetPic(original);
    changed.pixels = new RGB*[changed.dib_header_.height];
    for (int32_t i = 0; i < changed.dib_header_.height; i++) {
        changed.pixels[i] = new RGB[changed.dib_header_.width];
        for (int32_t j = 0; j < changed.dib_header_.width; j++) {
            changed.pixels[i][j] = MergePixelAndMatrix(original, j, i);
        }
    }
    return changed;
}

Filter* MakeSharpening(const Line& param) {
    if (param.size() != 1) {
        throw std::logic_error("Invalid arguments.");
    }
    if (param[0] != "-sharp") {
        throw std::logic_error("Invalid arguments.");
    }
    return new Sharpening();
}