#include "bmppicture.h"

constexpr int BitShift = 8;
constexpr double D = 255.0;

void OpenBMPPicture::UploadBMPPicture(const char* path) {
    std::ifstream pic;
    pic.open(path, std::ios::in | std::ios::binary);

    if (!pic.is_open()) {  // Проверка на корректность открытия файла
        cout << "File was not opened!" << endl;
        pic.close();
        throw std::invalid_argument("File was not opened!");
    }

    pic.read(reinterpret_cast<char*>(bitmap_file_header_), BITMAP_FILE_HEADER_SIZE);
    pic.read(reinterpret_cast<char*>(bitmap_info_), BITMAP_INFO_SIZE);

    if (bitmap_file_header_[0] != 'B' || bitmap_file_header_[1] != 'M') {  // Проверка на формат файла
        cout << "Incorrect file format (needed .bmp file)" << endl;
        pic.close();
        throw std::invalid_argument("Incorrect file format!");
    }

    pic_width_ = bitmap_info_[WH::width1] + (bitmap_info_[WH::width2] << BitShift) +
                 (bitmap_info_[WH::width3] << (BitShift * 2)) + (bitmap_info_[WH::width4] << (BitShift * 3));

    pic_height_ = bitmap_info_[WH::height1] + (bitmap_info_[WH::height2] << BitShift) +
                  (bitmap_info_[WH::height3] << (BitShift * 2)) + (bitmap_info_[WH::height4] << (BitShift * 3));

    int padding = ((4 - (pic_width_ * 3) % 4) %
                   4);  // кол-во бит, используемое для дополнения ячейки памяти о цвете до 4 байт (Подумать!)

    pixels_.resize(pic_height_, std::vector<Color>(pic_width_));
    for (size_t y = 0; y < pic_height_; ++y) {
        for (size_t x = 0; x < pic_width_; ++x) {
            unsigned char pix[3];
            pic.read(reinterpret_cast<char*>(pix), 3);
            pixels_[pic_height_ - y - 1][x].b = static_cast<double>(pix[0]) / D;
            pixels_[pic_height_ - y - 1][x].g = static_cast<double>(pix[1]) / D;
            pixels_[pic_height_ - y - 1][x].r = static_cast<double>(pix[2]) / D;
        }
        pic.ignore(padding);
    }
    cout << "File was opened!" << endl;
    pic.close();
}

std::vector<std::vector<Color>> OpenBMPPicture::GetColors() {
    return pixels_;
}

int OpenBMPPicture::GetHeight() {
    return pic_height_;
}

int OpenBMPPicture::GetWidth() {
    return pic_width_;
}

unsigned char* OpenBMPPicture::GetBitmapFileHeader() {
    return bitmap_file_header_;
}

unsigned char* OpenBMPPicture::GetBitmapInfo() {
    return bitmap_info_;
}
