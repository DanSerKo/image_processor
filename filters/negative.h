#pragma once

#include "filter.h"

class Negative : public Filter {
public:
    Negative() : Filter() {
    }
    ~Negative() override = default;
    Picture GetPic(const Picture& original) override;

private:
};
Filter* MakeNegative(const Line& param);