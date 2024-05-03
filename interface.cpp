#include "interface.h"

#include <vector>

Pipeline::~Pipeline() {
    for (auto& filter : filters_) {
        if (filter != nullptr) {
            delete filter;
            filter = nullptr;
        }
    }
}

void FilterFacturer::NewFilter(std::string name, MakeFilter func_maker) {
    maker_.insert({name, func_maker});
}

Filter* FilterFacturer::CreatFilter(const Line& parameters) {
    if (!maker_.count(parameters[0])) {
        throw std::runtime_error("Filter not declared.");
    }
    return maker_[parameters[0]](parameters);
}

std::vector<Line> Interface::Parser(int32_t argc, char* argv[]) {
    if (argc < 3) {
        throw std::runtime_error("Invalid arguments.");
    }
    std::vector<Line> result;
    read_file_ = argv[1];
    write_file_ = argv[2];
    for (size_t i = 3; i < argc; i++) {
        if (maker_.count(argv[i])) {
            result.push_back({argv[i]});
        } else {
            if (result.empty()) {
                throw std::logic_error("Invalid parametrs.");
            }
            result.back().push_back(argv[i]);
        }
    }
    return result;
}

void Pipeline::AddFilter(Filter* filter) {
    filters_.push_back(filter);
}

Picture Pipeline::GetChanged(const Picture& original) {
    Picture changed;
    changed = original;
    for (auto& filter : filters_) {
        changed = filter->GetPic(changed);
    }
    return changed;
}

void Interface::Start(int32_t argc, char* argv[]) {
    std::vector<Line> all_parametrs = Parser(argc, argv);
    for (auto& parametrs : all_parametrs) {
        pipeline_.AddFilter(CreatFilter(parametrs));
    }
    BMPReader read;
    read.Open(read_file_);
    read.ReadBMP(&picture_);
    Picture changed;
    changed = pipeline_.GetChanged(picture_);
    BMPWriter write;
    write.Open(write_file_);
    write.WriteBMP(&changed);
}
