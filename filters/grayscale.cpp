#include "grayscale.h"

Picture Grayscale::GetPic(const Picture& original) {
    Picture changed = Filter::GetPic(original);
    changed.pixels = new RGB*[changed.dib_header_.height];
    for (size_t i = 0; i < changed.dib_header_.height; i++) {
        changed.pixels[i] = new RGB[changed.dib_header_.width];
        for (size_t j = 0; j < changed.dib_header_.width; j++) {
            uint8_t gray = static_cast<uint8_t>(std::round(original.pixels[i][j].R * transf_r_ +
                                                           original.pixels[i][j].G * transf_g_ +
                                                           original.pixels[i][j].B * transf_b_));
            changed.pixels[i][j].R = gray;
            changed.pixels[i][j].G = gray;
            changed.pixels[i][j].B = gray;
        }
    }
    return changed;
}

Filter* MakeGrayscale(const Line& param) {
    if (param.size() != 1) {
        throw std::logic_error("Invalid arguments.");
    }
    if (param[0] != "-gs") {
        throw std::logic_error("Invalid arguments.");
    }
    return new Grayscale();
}