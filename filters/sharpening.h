#pragma once

#include "filter.h"

class Sharpening : public Filter, public MatrixMerger {
public:
    Sharpening() : Filter(), MatrixMerger() {
        ChangeMatrix({{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}});  // NOLINT
    }
    ~Sharpening() override = default;
    Picture GetPic(const Picture& original) override;

private:
};
Filter* MakeSharpening(const Line& param);
