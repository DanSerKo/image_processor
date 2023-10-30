#include "bmp_reader.h"

BMPReader::~BMPReader() {
    Close();
}

void BMPReader::ReadBMP(Picture* picture) {
    if (!IsOpen()) {
        throw std::logic_error("File is not open.");
    }
    if (picture == nullptr) {
        throw std::logic_error("Picture not found.");
    }
    file_.seekg(0);
    ReadBmpHeader(picture);
    ReadDibHeader(picture);
    ReadPixels(picture);
}

void BMPReader::Open(const std::string& filename) {
    if (file_.is_open()) {
        throw std::logic_error("File is already open.");
    }
    if (filename.empty()) {
        throw std::invalid_argument("Filename is empty.");
    }
    filename_ = filename;
    file_.open(filename_);
    if (!file_.is_open()) {
        throw std::runtime_error("Can't open file.");
    }
}

void BMPReader::Close() {
    file_.close();
    filename_.clear();
}

void BMPReader::ReadBmpHeader(Picture* picture) {
    if (!file_.is_open()) {
        throw std::logic_error("Can't open file.");
    }
    file_.read(reinterpret_cast<char*>(&picture->bmp_header_), sizeof(BMPheader));
    if (!file_.is_open()) {
        throw std::logic_error("Can't open file.");
    }

    if (picture->bmp_header_.sign != BMP_SIGN) {
        throw std::runtime_error("BMP file is not correct.");
    }
    if (picture->bmp_header_.offset != sizeof(picture->bmp_header_) + sizeof(picture->dib_header_)) {
        throw std::runtime_error("BMP file is not correct.");
    }
}

void BMPReader::ReadDibHeader(Picture* picture) {
    if (!file_.is_open()) {
        throw std::logic_error("Can't open file.");
    }
    file_.read(reinterpret_cast<char*>(&picture->dib_header_), sizeof(DIBheader));
    if (!file_.is_open()) {
        throw std::logic_error("Can't open file.");
    }
    if (picture->dib_header_.width <= 0 || picture->dib_header_.height <= 0) {
        throw std::runtime_error("BMP file is not correct.");
    }
    if (picture->dib_header_.color_planes_num != 1) {
        throw std::runtime_error("BMP file is not correct.");
    }
    if (picture->dib_header_.bits_per_pixel != BITS_PIXEL) {
        throw std::runtime_error("BMP file is not correct.");
    }
}

void BMPReader::ReadPixels(Picture* picture) {
    if (!file_.is_open()) {
        throw std::logic_error("Can't open file.");
    }
    int32_t height = picture->dib_header_.height;
    int32_t width = picture->dib_header_.width;
    int32_t row_stride = picture->dib_header_.width * static_cast<int32_t>(sizeof(RGB));
    int32_t trash_size = (4 - row_stride % 4) % 4;
    uint8_t* trash = new uint8_t[trash_size];
    picture->pixels = new RGB*[height];
    for (size_t i = 0; i < height; i++) {
        picture->pixels[i] = new RGB[width];
        file_.read(reinterpret_cast<char*>(picture->pixels[i]), row_stride);
        if (trash_size != 0) {
            file_.read(reinterpret_cast<char*>(trash), trash_size);
        }
    }
    delete[] trash;
}
