#pragma once

#include "filter.h"

class Crop : public Filter {
public:
    Crop(int32_t width, int32_t height) : Filter() {
        width_ = width;
        height_ = height;
    }
    ~Crop() override = default;
    Picture GetPic(const Picture& original) override;

private:
    int32_t width_;
    int32_t height_;
};
Filter* MakeCrop(const Line& param);
