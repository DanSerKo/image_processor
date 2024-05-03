#pragma once

#include "../bmp_utilities/bmp_reader.h"
#include "../bmp_utilities/bmp_writer.h"

#include <cmath>
#include <limits>
#include <string>
#include <vector>

using Line = std::vector<std::string>;

const int32_t MAX_PIXEL_VALUE = std::numeric_limits<uint8_t>::max();

class Filter {
public:
    Filter() {
    }
    virtual ~Filter() = default;
    // Возвращает изоброжение после фильтра.
    virtual Picture GetPic(const Picture& original);

private:
};

class MatrixMerger {
public:
    MatrixMerger() {
    }
    virtual ~MatrixMerger() = default;
    void ChangeMatrix(const std::vector<std::vector<int32_t>>& matrix);
    // Возвращает пиксель после матицы
    RGB MergePixelAndMatrix(const Picture& original, int32_t x, int32_t y);

protected:
    std::vector<std::vector<int32_t>> matrix_;
};