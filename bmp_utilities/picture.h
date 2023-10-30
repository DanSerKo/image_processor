#pragma once

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

const uint16_t BMP_SIGN = 0x4D42;  // BM
const int32_t BITS_PIXEL = 24;

// Работает с GCC
struct BMPheader {
    uint16_t sign;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
} __attribute__((packed));

struct DIBheader {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t color_planes_num;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t img_size;
    int32_t hor_res;
    int32_t ver_res;
    uint32_t colors_num;
    uint32_t important_colors_num;
} __attribute__((packed));

struct RGB {
    uint8_t B;
    uint8_t G;
    uint8_t R;
} __attribute__((packed));

class Picture {
public:
    Picture() {
        pixels = nullptr;
    }
    Picture(const Picture& copy);
    Picture(Picture&& copy);
    ~Picture();
    BMPheader bmp_header_;
    DIBheader dib_header_;
    RGB** pixels;
    Picture& operator=(Picture copy);
    void Clear();

private:
    void Swap(Picture& copy);
};
