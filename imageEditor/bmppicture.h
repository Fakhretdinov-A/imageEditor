#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include "color.h"

enum WH {  // Width & Height
    width1 = 4,
    width2,
    width3,
    width4,
    height1,
    height2,
    height3,
    height4
};
using std::cout;
using std::endl;

class OpenBMPPicture;

class Picture {  // Класс картинки
protected:
    int pic_height_;
    int pic_width_;
    unsigned char* file_header_;
    unsigned char* info_;
    std::vector<std::vector<Color>> pixels_;  // Вектор, хранящий цвет каждого пикселя
    std::vector<std::vector<Color>> pixels_copy_;  // Копия пикселей

public:
    explicit Picture(OpenBMPPicture&);
    Picture(int, int);
    Color GetColor(int, int);
    Color GetOriginalColor(size_t, size_t);
    const void SetColor(int, int, Color);
    const void Resize(int, int);
    int GetHeight() const;
    int GetWidth() const;
    void SetHeight(int);
    void SetWidth(int);
    unsigned char* GetBitmapFileHeader() const;
    unsigned char* GetBitmapInfo() const;
    std::vector<std::vector<Color>> GetColors();
    void SetOriginal();
    Color GetValidColor(size_t, size_t) const;
};
class BMPPicture {
protected:
    int pic_height_;
    int pic_width_;
    std::vector<std::vector<Color>> pixels_;
    static const int BITMAP_FILE_HEADER_SIZE = 14;
    static const int BITMAP_INFO_SIZE = 40;
    unsigned char bitmap_file_header_[BITMAP_FILE_HEADER_SIZE];
    unsigned char bitmap_info_[BITMAP_INFO_SIZE];
};

class OpenBMPPicture : public BMPPicture {  // Класс открытия картинки
public:
    void UploadBMPPicture(const char* path);
    std::vector<std::vector<Color>> GetColors();
    int GetHeight();
    int GetWidth();
    unsigned char* GetBitmapFileHeader();
    unsigned char* GetBitmapInfo();
};

class ExportBMPPicture : public BMPPicture {  // Класс экспорта картинки
protected:
    unsigned char* bitmap_file_header_;
    unsigned char* bitmap_info_;

public:
    explicit ExportBMPPicture(Picture&);
    void Export(const char* path);
};
