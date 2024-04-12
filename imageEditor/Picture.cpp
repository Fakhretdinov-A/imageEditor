#include "bmppicture.h"

Picture::Picture(OpenBMPPicture& bmp) {
    pic_height_ = bmp.GetHeight();
    pic_width_ = bmp.GetWidth();
    pixels_ = bmp.GetColors();
    info_ = bmp.GetBitmapInfo();
    file_header_ = bmp.GetBitmapFileHeader();
}

Picture::Picture(int h, int w) {
    pic_height_ = h;
    pic_width_ = w;
    pixels_ = std::vector<std::vector<Color>>(h, std::vector<Color>(w));
}

Color Picture::GetColor(int y, int x) {
    return pixels_[y][x];
}

int Picture::GetHeight() const {
    return pic_height_;
}

int Picture::GetWidth() const {
    return pic_width_;
}

void Picture::SetHeight(int h) {
    pic_height_ = h;
}

void Picture::SetWidth(int w) {
    pic_width_ = w;
}

unsigned char* Picture::GetBitmapFileHeader() const {
    return file_header_;
}

unsigned char* Picture::GetBitmapInfo() const {
    return info_;
}

const void Picture::SetColor(int y, int x, Color c) {
    pixels_[y][x] = c;
}

const void Picture::Resize(int n, int m) {
    pixels_.resize(n, std::vector<Color>(m));
}

std::vector<std::vector<Color>> Picture::GetColors() {
    return pixels_;
}

Color Picture::GetOriginalColor(size_t y, size_t x) {
    return pixels_copy_[y][x];
}

void Picture::SetOriginal() {
    pixels_copy_ = pixels_;
}

Color Picture::GetValidColor(size_t x, size_t y) const {
    if (x >= pic_width_) {
        x = x > std::numeric_limits<size_t>::max() / 2 ? 0 : (pic_width_ - 1);
    }
    if (y >= pic_height_) {
        y = y > std::numeric_limits<size_t>::max() / 2 ? 0 : (pic_height_ - 1);
    }
    return pixels_[y][x];
}
