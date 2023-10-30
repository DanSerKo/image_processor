#include "edge_detection.h"

Picture EdgeDetection::GetPic(const Picture& original) {
    Picture grayscale = Grayscale::GetPic(original);
    Picture changed = Filter::GetPic(grayscale);
    changed.pixels = new RGB*[changed.dib_header_.height];
    for (int32_t i = 0; i < changed.dib_header_.height; i++) {
        changed.pixels[i] = new RGB[changed.dib_header_.width];
        for (int32_t j = 0; j < changed.dib_header_.width; j++) {
            changed.pixels[i][j] = MergePixelAndMatrix(grayscale, j, i);
            if (changed.pixels[i][j].R > threshold_) {
                changed.pixels[i][j].R = MAX_PIXEL_VALUE;
                changed.pixels[i][j].G = MAX_PIXEL_VALUE;
                changed.pixels[i][j].B = MAX_PIXEL_VALUE;
            } else {
                changed.pixels[i][j].R = 0;
                changed.pixels[i][j].G = 0;
                changed.pixels[i][j].B = 0;
            }
        }
    }
    return changed;
}

Filter* MakeEdgeDetection(const Line& param) {
    if (param.size() != 2) {
        throw std::logic_error("Invalid arguments.");
    }
    if (param[0] != "-edge") {
        throw std::logic_error("Invalid arguments.");
    }
    double threshold = -1;
    try {
        threshold = stod(param[1]);
    } catch (std::exception& e) {
        throw std::logic_error("Invalid arguments");
    }
    return new EdgeDetection(static_cast<int32_t>(threshold * MAX_PIXEL_VALUE));
}
