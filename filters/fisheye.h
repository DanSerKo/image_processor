#pragma once

#include "filter.h"

class Fisheye : public Filter {
public:
    explicit Fisheye(int32_t strength) : Filter() {
        strength_ = strength;
    }
    ~Fisheye() override = default;
    Picture GetPic(const Picture& original) override;

private:
    double Dist(int32_t diffx, int32_t diffy);

    int32_t strength_;
};
Filter* MakeFisheye(const Line& param);
