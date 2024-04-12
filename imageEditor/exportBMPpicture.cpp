#include "bmppicture.h"

constexpr double D = 255.0;
constexpr int BitShift = 8;

ExportBMPPicture::ExportBMPPicture(Picture &p) {
    pic_height_ = p.GetHeight();
    pic_width_ = p.GetWidth();
    pixels_ = p.GetColors();
    bitmap_info_ = p.GetBitmapInfo();
    bitmap_file_header_ = p.GetBitmapFileHeader();
}

void ExportBMPPicture::Export(const char *path) {
    std::ofstream file;
    file.open(path, std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        cout << "File was not opened!" << endl;
        file.close();
        throw std::invalid_argument("File was not opened!");
    }
    // Задаём ширину и высоту картинки
    bitmap_info_[WH::width1] = pic_width_;
    bitmap_info_[WH::width2] = pic_width_ >> BitShift;
    bitmap_info_[WH::width3] = pic_width_ >> (BitShift * 2);
    bitmap_info_[WH::width4] = pic_width_ >> (BitShift * 3);
    bitmap_info_[WH::height1] = pic_height_;
    bitmap_info_[WH::height2] = pic_height_ >> BitShift;
    bitmap_info_[WH::height3] = pic_height_ >> (BitShift * 2);
    bitmap_info_[WH::height4] = pic_height_ >> (BitShift * 3);

    file.write(reinterpret_cast<char *>(bitmap_file_header_), BITMAP_FILE_HEADER_SIZE);
    file.write(reinterpret_cast<char *>(bitmap_info_), BITMAP_INFO_SIZE);
    int padding_size = ((4 - (pic_width_ * 3) % 4) %
                        4);  // кол-во бит, используемое для дополнения ячейки памяти о цвете до 4 байт (Подумать!)
    unsigned char padding[3] = {0, 0, 0};

    for (size_t y = 0; y < pic_height_; ++y) {
        for (size_t x = 0; x < pic_width_; ++x) {
            unsigned char red = static_cast<unsigned char>(pixels_[pic_height_ - y - 1][x].r * D);
            unsigned char green = static_cast<unsigned char>(pixels_[pic_height_ - y - 1][x].g * D);
            unsigned char blue = static_cast<unsigned char>(pixels_[pic_height_ - y - 1][x].b * D);

            unsigned char pixel[] = {blue, green, red};
            file.write(reinterpret_cast<char *>(pixel), 3);
        }
        file.write(reinterpret_cast<char *>(padding), padding_size);
    }

    file.close();
    cout << "The program has successfully completed the work!" << endl;
}
