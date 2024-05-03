#pragma once

#include "filter.h"
#include "grayscale.h"

class EdgeDetection : public Grayscale, public MatrixMerger {
public:
    explicit EdgeDetection(int32_t threshold) : Grayscale(), MatrixMerger() {
        threshold_ = threshold;
        ChangeMatrix({{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}});
    }
    ~EdgeDetection() override = default;
    Picture GetPic(const Picture& original) override;

private:
    int32_t threshold_;
};
Filter* MakeEdgeDetection(const Line& param);
