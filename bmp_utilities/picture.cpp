#include "picture.h"

Picture::Picture(const Picture& copy) {
    bmp_header_ = copy.bmp_header_;
    dib_header_ = copy.dib_header_;
    pixels = new RGB*[dib_header_.height];
    for (int i = 0; i < dib_header_.height; i++) {
        pixels[i] = new RGB[dib_header_.width];
        for (int j = 0; j < dib_header_.width; j++) {
            pixels[i][j] = copy.pixels[i][j];
        }
    }
}

Picture::Picture(Picture&& copy) {
    bmp_header_ = copy.bmp_header_;
    dib_header_ = copy.dib_header_;
    pixels = copy.pixels;
}

Picture& Picture::operator=(Picture copy) {
    Swap(copy);
    return *this;
}

Picture::~Picture() {
    Clear();
}

void Picture::Clear() {
    if (pixels != nullptr) {
        for (size_t i = 0; i < dib_header_.height; i++) {
            delete[] pixels[i];
        }
        delete[] pixels;
        pixels = nullptr;
    }
}

void Picture::Swap(Picture& second) {
    std::swap(bmp_header_, second.bmp_header_);
    std::swap(dib_header_, second.dib_header_);
    std::swap(pixels, second.pixels);
}