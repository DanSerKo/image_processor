#pragma once

#include "picture.h"

class BMPWriter {
public:
    BMPWriter() {
    }
    ~BMPWriter();
    // Записывает в заданный файл
    void WriteBMP(Picture* picture);
    void Open(const std::string& filename);
    void Close();
    bool IsOpen() const {
        return file_.is_open();
    }
    const std::string& GetFilename() const {
        return filename_;
    }

protected:
    void WriteBmpHeader(Picture* picture);
    void WriteDibHeader(Picture* picture);
    void WritePixels(Picture* picture);

    std::string filename_;
    std::fstream file_;
};
