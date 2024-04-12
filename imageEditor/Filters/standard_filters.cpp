#include "standard_filters.h"

void Grayscale::ApplyFilter(Picture &p) {
    const int h = p.GetHeight();
    const int w = p.GetWidth();
    const double redscale = 0.299;
    const double greenscale = 0.587;
    const double bluescale = 0.114;
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            Color c;
            double param =
                p.GetColor(y, x).r * redscale + p.GetColor(y, x).g * greenscale + p.GetColor(y, x).b * bluescale;
            c = {param, param, param};
            p.SetColor(y, x, c);
        }
    }
}

void Negative::ApplyFilter(Picture &p) {
    const unsigned int h = p.GetHeight();
    const unsigned int w = p.GetWidth();
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            Color c = p.GetColor(y, x);
            p.SetColor(y, x, {1 - c.r, 1 - c.g, 1 - c.b});
        }
    }
}

Crop::Crop(int w, int h) {
    width_ = w;
    height_ = h;
}

void Crop::ApplyFilter(Picture &p) {
    height_ = std::min(p.GetHeight(), height_);
    width_ = std::min(p.GetWidth(), width_);
    p.Resize(height_, width_);
    p.SetWidth(width_);
    p.SetHeight(height_);
}

GaussianBlur::GaussianBlur(double sigma) {
    sigma = std::abs(sigma);
    const size_t size = static_cast<size_t>(std::ceil(6 * sigma)) | 1;
    params_.resize(size);
    for (int dx = 0; dx <= static_cast<int>(size / 2); ++dx) {
        params_[size / 2 - dx] = params_[size / 2 + dx] =
            std::exp(-static_cast<double>(dx * dx) / (2 * pow(sigma, 2))) / std::sqrt(2 * M_PI * pow(sigma, 2));
    }
}

void GaussianBlur::ApplyFilter(Picture &picture) {
    const auto size_h = static_cast<int>(params_.size() / 2);
    Picture picture_copy(picture.GetHeight(), picture.GetWidth());

    for (size_t x = 0; x < static_cast<size_t>(picture.GetWidth()); ++x) {
        for (size_t y = 0; y < static_cast<size_t>(picture.GetHeight()); ++y) {
            Color pixel = picture_copy.GetValidColor(x, y);
            for (int dy = -size_h; dy <= size_h; ++dy) {
                pixel.r += picture.GetValidColor(x, y + dy).r * params_[dy + size_h];
                pixel.g += picture.GetValidColor(x, y + dy).g * params_[dy + size_h];
                pixel.b += picture.GetValidColor(x, y + dy).b * params_[dy + size_h];
            }
            picture_copy.SetColor(static_cast<int>(y), static_cast<int>(x), pixel);
        }
    }

    for (size_t y = 0; y < static_cast<size_t>(picture_copy.GetHeight()); ++y) {
        for (size_t x = 0; x < static_cast<size_t>(picture_copy.GetWidth()); ++x) {
            Color pixel = picture.GetColor(static_cast<int>(y), static_cast<int>(x));
            pixel = {0.0, 0.0, 0.0};
            for (int dx = -size_h; dx <= size_h; ++dx) {
                pixel.r += picture_copy.GetValidColor(x + dx, y).r * params_[dx + size_h];
                pixel.g += picture_copy.GetValidColor(x + dx, y).g * params_[dx + size_h];
                pixel.b += picture_copy.GetValidColor(x + dx, y).b * params_[dx + size_h];
            }
            picture.SetColor(static_cast<int>(y), static_cast<int>(x), pixel);
        }
    }
}
