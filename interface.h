#pragma once

#include "filters/blur.h"
#include "filters/crop.h"
#include "filters/edge_detection.h"
#include "filters/fisheye.h"
#include "filters/grayscale.h"
#include "filters/negative.h"
#include "filters/sharpening.h"

#include <map>
#include <string>
#include <vector>

using MakeFilter = Filter* (*)(const Line&);

class FilterFacturer {
public:
    FilterFacturer() {
        NewFilter("-crop", MakeCrop);
        NewFilter("-gs", MakeGrayscale);
        NewFilter("-neg", MakeNegative);
        NewFilter("-sharp", MakeSharpening);
        NewFilter("-edge", MakeEdgeDetection);
        NewFilter("-fish", MakeFisheye);
        NewFilter("-blur", MakeGaussianBlur);
    }
    ~FilterFacturer() = default;
    // Cоздает фильтр по заданным параметрам
    Filter* CreatFilter(const Line& parameters);

protected:
    std::map<std::string, MakeFilter> maker_;

private:
    void NewFilter(std::string name, MakeFilter func_maker);
};

class Pipeline {
public:
    Pipeline() {
    }
    ~Pipeline();
    void AddFilter(Filter* filter);
    // Возвращает изоброжение после всех фильтров
    Picture GetChanged(const Picture& original);

private:
    std::vector<Filter*> filters_;
};

class Interface : public FilterFacturer {
public:
    Interface() : FilterFacturer() {
    }
    ~Interface() = default;
    void Start(int32_t argc, char* argv[]);

protected:
    std::vector<Line> Parser(int32_t argc, char* argv[]);

    Picture picture_;
    std::string read_file_;
    std::string write_file_;
    Pipeline pipeline_;
};
