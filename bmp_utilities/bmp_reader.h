#pragma once

#include "picture.h"

class BMPReader {
public:
    BMPReader() {
    }
    ~BMPReader();
    // Считывает файл
    void ReadBMP(Picture* picture);
    void Open(const std::string& filename);
    void Close();
    bool IsOpen() const {
        return file_.is_open();
    }
    const std::string& GetFilename() const {
        return filename_;
    }

protected:
    // Считываем bmp header
    void ReadBmpHeader(Picture* picture);
    // Считываем dib header
    void ReadDibHeader(Picture* picture);
    // Считываем пиксели
    void ReadPixels(Picture* picture);

    std::string filename_;
    std::fstream file_;
};
