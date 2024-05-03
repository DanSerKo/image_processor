#include "blur.h"

const double PI = acos(-1);
const double EPS = 1e-4;

void GaussianBlur::WidthBlur(int32_t height, int32_t width, Picture& changed, const std::vector<double>& func_pixel,
                             const Picture& original) {
    for (int32_t i = 0; i < height; i++) {
        for (int32_t j = 0; j < width; j++) {
            double r = 0;
            double g = 0;
            double b = 0;
            for (int32_t x = 0; x < width && func_pixel[x] > EPS; x++) {
                int32_t t = j + x;
                double f_x = func_pixel[x];
                r += f_x * static_cast<double>(original.pixels[i][std::min(t, width - 1)].R);
                g += f_x * static_cast<double>(original.pixels[i][std::min(t, width - 1)].G);
                b += f_x * static_cast<double>(original.pixels[i][std::min(t, width - 1)].B);
            }
            for (int32_t x = 1; x < width && func_pixel[x] > EPS; x++) {
                int32_t t = j - x;
                double f_x = func_pixel[x];
                r += f_x * static_cast<double>(original.pixels[i][std::max(t, 0)].R);
                g += f_x * static_cast<double>(original.pixels[i][std::max(t, 0)].G);
                b += f_x * static_cast<double>(original.pixels[i][std::max(t, 0)].B);
            }
            changed.pixels[i][j].R = static_cast<uint8_t>(r);
            changed.pixels[i][j].G = static_cast<uint8_t>(g);
            changed.pixels[i][j].B = static_cast<uint8_t>(b);
        }
    }
}

void GaussianBlur::HeightBlur(int32_t height, int32_t width, Picture& changed, const std::vector<double>& func_pixel,
                              const Picture& original) {
    for (int32_t i = 0; i < height; i++) {
        for (int32_t j = 0; j < width; j++) {
            double r = 0;
            double g = 0;
            double b = 0;
            for (int32_t y = 0; y < height && func_pixel[y] > EPS; y++) {
                int32_t t = i + y;
                double f_y = func_pixel[y];
                r += f_y * static_cast<double>(original.pixels[std::min(t, height - 1)][j].R);
                g += f_y * static_cast<double>(original.pixels[std::min(t, height - 1)][j].G);
                b += f_y * static_cast<double>(original.pixels[std::min(t, height - 1)][j].B);
            }
            for (int32_t y = 1; y < height && func_pixel[y] > EPS; y++) {
                int32_t t = i - y;
                double f_y = func_pixel[y];
                r += f_y * static_cast<double>(original.pixels[std::max(t, 0)][j].R);
                g += f_y * static_cast<double>(original.pixels[std::max(t, 0)][j].G);
                b += f_y * static_cast<double>(original.pixels[std::max(t, 0)][j].B);
            }
            changed.pixels[i][j].R = static_cast<uint8_t>(r);
            changed.pixels[i][j].G = static_cast<uint8_t>(g);
            changed.pixels[i][j].B = static_cast<uint8_t>(b);
        }
    }
}

Picture GaussianBlur::GetPic(const Picture& original) {
    Picture changed = Filter::GetPic(original);
    int32_t height = changed.dib_header_.height;
    int32_t width = changed.dib_header_.width;
    changed.pixels = new RGB*[height];
    for (int32_t i = 0; i < height; i++) {
        changed.pixels[i] = new RGB[width];
    }
    int32_t mx = std::max(height, width);
    std::vector<double> func_pixel(mx);
    for (int32_t i = 0; i < mx; i++) {
        func_pixel[i] = exp(-(static_cast<double>(i) * i / (2 * sigma_ * sigma_))) / sqrt(2 * PI * sigma_ * sigma_);
    }
    HeightBlur(height, width, changed, func_pixel, original);
    Picture original2 = changed;
    WidthBlur(height, width, changed, func_pixel, original2);
    return changed;
}

Filter* MakeGaussianBlur(const Line& param) {
    if (param.size() != 2) {
        throw std::logic_error("Invalid arguments.");
    }
    if (param[0] != "-blur") {
        throw std::logic_error("Invalid arguments.");
    }
    double sigma = -1;
    try {
        sigma = stod(param[1]);
    } catch (std::exception& e) {
        throw std::logic_error("Invalid arguments");
    }
    return new GaussianBlur(sigma);
}
