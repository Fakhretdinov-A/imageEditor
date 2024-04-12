#include "my_filters.h"

RotatePicture::RotatePicture(double a) : angle_(a) {
}

void RotatePicture::ApplyFilter(Picture &picture) {
    const double angle = static_cast<double>(angle_ * 0.0174533);
    const double cos_a = static_cast<double>(cos(angle));
    const double sin_a = static_cast<double>(sin(angle));
    const int h = picture.GetHeight();
    const int w = picture.GetWidth();
    const double d = 2;
    std::vector<std::vector<double>> rotation_matrix{{cos_a, -sin_a}, {sin_a, cos_a}};

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            double x = static_cast<double>(j) - static_cast<double>(w) / d;  // центрирование вокруг начала координат
            double y = static_cast<double>(h) / d - static_cast<double>(i);
            double new_x = static_cast<double>(x * rotation_matrix[0][0] + y * rotation_matrix[0][1]);
            double new_y = static_cast<double>(x * rotation_matrix[1][0] + y * rotation_matrix[1][1]);
            int new_i = static_cast<int>(static_cast<double>(h) / d - round(new_y));
            int new_j = static_cast<int>(round(new_x) + static_cast<double>(w) / d);

            if (new_i >= 0 && new_i < h && new_j >= 0 && new_j < w) {
                picture.SetColor(j, i, picture.GetOriginalColor(new_j, new_i));
            }
        }
    }
}

void Minecraft::ApplyFilter(Picture &picture) {
    const int w = picture.GetWidth();
    const int h = picture.GetHeight();
    const int block_size = 32;
    const int rows = h / block_size;
    const int cols = w / block_size;
    const double d = 255.0f;

    std::vector<std::vector<Color>> colors(rows, std::vector<Color>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int block_left = j * block_size;
            int block_top = i * block_size;

            int total_red = 0;
            int total_green = 0;
            int total_blue = 0;

            for (int x = 0; x < block_size; x++) {
                for (int y = 0; y < block_size; y++) {
                    int pixel_x = block_left + x;
                    int pixel_y = block_top + y;

                    Color pixel_color = picture.GetColor(pixel_y, pixel_x);

                    total_red += static_cast<int>(pixel_color.r * d);
                    total_green += static_cast<int>(pixel_color.g * d);
                    total_blue += static_cast<int>(pixel_color.b * d);
                }
            }

            int pixels_per_block = block_size * block_size;
            int avg_red = total_red / pixels_per_block;
            int avg_green = total_green / pixels_per_block;
            int avg_blue = total_blue / pixels_per_block;

            colors[i][j].r = static_cast<double>(avg_red) / d;
            colors[i][j].g = static_cast<double>(avg_green) / d;
            colors[i][j].b = static_cast<double>(avg_blue) / d;
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int block_left = j * block_size;
            int block_top = i * block_size;
            Color block_color = colors[i][j];

            for (int x = 0; x < block_size; x++) {
                for (int y = 0; y < block_size; y++) {
                    int pixel_x = block_left + x;
                    int pixel_y = block_top + y;

                    picture.SetColor(pixel_y, pixel_x, block_color);
                }
            }
        }
    }
}

void Glass::ApplyFilter(Picture &picture) {
    const unsigned int width = picture.GetWidth();
    const unsigned int height = picture.GetHeight();
    const double pi = 3.14159265;
    const double x_f = param1 * pi / param2;  // 16 or 2, 50 or 25
    const double y_f = param1 * pi / param2;
    const double p = 50 * pi / 720;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            const double d_x = 10 * sin(x * x_f + p);
            const double d_y = 10 * sin(y * y_f);
            const int src_x = static_cast<int>(x + d_x);
            const int src_y = static_cast<int>(y + d_y);
            if (src_x >= 0 && src_x < width && src_y >= 0 && src_y < height) {
                picture.SetColor(y, x, picture.GetColor(src_y, src_x));
            }
        }
    }
}

enum c { p1 = 25, p2 = 50 };
void Strange1::ApplyFilter(Picture &picture) {
    param1 = pm;
    param2 = c::p1;
    Glass::ApplyFilter(picture);
}

void Strange2::ApplyFilter(Picture &picture) {
    param1 = pm;
    param2 = c::p2;
    Glass::ApplyFilter(picture);
}
