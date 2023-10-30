#include "bmp_writer.h"

BMPWriter::~BMPWriter() {
    Close();
}

void BMPWriter::WriteBMP(Picture* picture) {
    if (!IsOpen()) {
        throw std::logic_error("File is not open.");
    }
    if (picture == nullptr) {
        throw std::logic_error("Picture not found.");
    }
    WriteBmpHeader(picture);
    WriteDibHeader(picture);
    WritePixels(picture);
}

void BMPWriter::Open(const std::string& filename) {
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

void BMPWriter::Close() {
    file_.close();
    filename_.clear();
}

void BMPWriter::WriteBmpHeader(Picture* picture) {
    if (!file_.is_open()) {
        throw std::logic_error("Can't open file.");
    }
    file_.write(reinterpret_cast<char*>(&picture->bmp_header_), sizeof(BMPheader));
    if (!file_.is_open()) {
        throw std::logic_error("Can't open file.");
    }
}

void BMPWriter::WriteDibHeader(Picture* picture) {
    if (!file_.is_open()) {
        throw std::logic_error("Can't open file.");
    }
    file_.write(reinterpret_cast<char*>(&picture->dib_header_), sizeof(DIBheader));
    if (!file_.is_open()) {
        throw std::logic_error("Can't open file.");
    }
}

void BMPWriter::WritePixels(Picture* picture) {
    if (!file_.is_open()) {
        throw std::logic_error("Can't open file.");
    }
    int32_t row_stride = picture->dib_header_.width * static_cast<int32_t>(sizeof(RGB));
    int32_t trash_size = (4 - row_stride % 4) % 4;
    uint8_t* trash = new uint8_t[trash_size];
    for (size_t i = 0; i < trash_size; i++) {
        trash[i] = 0;
    }
    for (size_t i = 0; i < picture->dib_header_.height; i++) {
        file_.write(reinterpret_cast<char*>(picture->pixels[i]), row_stride);
        if (trash_size != 0) {
            file_.write(reinterpret_cast<char*>(trash), trash_size);
        }
    }
    delete[] trash;
}
