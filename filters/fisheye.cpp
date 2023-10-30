#include "fisheye.h"

double Fisheye::Dist(int32_t diffx, int32_t diffy) {
    return sqrt(diffx * diffx + diffy * diffy);
}

Picture Fisheye::GetPic(const Picture& original) {
    Picture changed = Filter::GetPic(original);
    int32_t width = original.dib_header_.width;
    int32_t height = original.dib_header_.height;
    int32_t cx = width / 2;
    int32_t cy = height / 2;
    double radius = Dist(width, height) / strength_;

    changed.pixels = new RGB*[height];
    for (size_t i = 0; i < height; i++) {
        changed.pixels[i] = new RGB[width];
    }
    for (int32_t i = 0; i < width; i++) {
        for (int32_t j = 0; j < height; j++) {
            int32_t diffx = i - cx;
            int32_t diffy = j - cy;
            double inv_distance = Dist(cy, cx) - Dist(diffx, diffy);
            double r = inv_distance / radius;
            double theta = 1;
            if (r != 0) {
                theta = atan(r) / r;
            }
            int32_t hisx = static_cast<int32_t>(cx + theta * diffx);
            int32_t hisy = static_cast<int32_t>(cy + theta * diffy);
            changed.pixels[j][i] = original.pixels[hisy][hisx];
        }
    }
    return changed;
}

Filter* MakeFisheye(const Line& param) {
    if (param.size() != 2) {
        throw std::logic_error("Invalid arguments.");
    }
    if (param[0] != "-fish") {
        throw std::logic_error("Invalid arguments.");
    }
    int32_t strength = 0;
    try {
        strength = stoi(param[1]);
    } catch (std::exception& e) {
        throw std::logic_error("Invalid arguments");
    }
    if (strength <= 0) {
        throw std::logic_error("Invalid arguments.");
    }
    return new Fisheye(strength);
}