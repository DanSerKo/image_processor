#include "filter.h"
#include <cstdint>

Picture Filter::GetPic(const Picture& original) {
    Picture changed;
    changed.bmp_header_ = original.bmp_header_;
    changed.dib_header_ = original.dib_header_;
    changed.dib_header_.hor_res = 0;
    changed.dib_header_.ver_res = 0;
    changed.dib_header_.img_size = 0;
    return changed;
}

RGB MatrixMerger::MergePixelAndMatrix(const Picture& original, int32_t x, int32_t y) {
    RGB result;
    int32_t r = 0;
    int32_t g = 0;
    int32_t b = 0;
    int32_t dist = static_cast<int32_t>(matrix_.size()) / 2;
    for (int32_t i = -dist; i <= dist; i++) {
        for (int32_t j = -dist; j <= dist; j++) {
            int32_t now_y = std::min(std::max(y + i, 0), original.dib_header_.height - 1);
            int32_t now_x = std::min(std::max(x + j, 0), original.dib_header_.width - 1);
            r += original.pixels[now_y][now_x].R * matrix_[1 + i][1 + j];
            g += original.pixels[now_y][now_x].G * matrix_[1 + i][1 + j];
            b += original.pixels[now_y][now_x].B * matrix_[1 + i][1 + j];
        }
    }
    result.R = std::min(MAX_PIXEL_VALUE, std::max(0, r));
    result.G = std::min(MAX_PIXEL_VALUE, std::max(0, g));
    result.B = std::min(MAX_PIXEL_VALUE, std::max(0, b));
    return result;
}

void MatrixMerger::ChangeMatrix(const std::vector<std::vector<int32_t>>& matrix) {
    if (matrix.size() % 2 != 1) {
        throw std::logic_error("Invalid matrix.");
    }
    for (auto& line : matrix) {
        if (line.size() != matrix.size()) {
            throw std::logic_error("Invalid matrix.");
        }
    }
    matrix_ = matrix;
}