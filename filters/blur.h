#pragma once

#include "filter.h"

class GaussianBlur : public Filter {
public:
    explicit GaussianBlur(double sigma) : Filter() {
        sigma_ = sigma;
    }
    ~GaussianBlur() override = default;
    Picture GetPic(const Picture& original) override;

private:
    void WidthBlur(int32_t height, int32_t width, Picture& changed, const std::vector<double>& func_pixel,
                   const Picture& original);
    void HeightBlur(int32_t height, int32_t width, Picture& changed, const std::vector<double>& func_pixel,
                    const Picture& original);

    double sigma_;
};
Filter* MakeGaussianBlur(const Line& param);
