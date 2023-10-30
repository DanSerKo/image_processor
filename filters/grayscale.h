#pragma once

#include "filter.h"

class Grayscale : public Filter {
public:
    Grayscale() : Filter() {
    }
    ~Grayscale() override = default;
    Picture GetPic(const Picture& original) override;

private:
    const double transf_r_ = 0.299;
    const double transf_g_ = 0.587;
    const double transf_b_ = 0.114;
};
Filter* MakeGrayscale(const Line& param);
