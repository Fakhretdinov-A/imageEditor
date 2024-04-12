#include "matrix_filters.h"

constexpr double D = 0.01;
constexpr int S = 9;

std::vector<Color> GetNeighbours(Picture &p, int y, int x) {
    std::vector<Color> matrix(S);
    const int w = p.GetWidth();
    const int h = p.GetHeight();

    if (y == 0) {      // первая строка
        if (x == 0) {  // первый столбец
            matrix = {p.GetOriginalColor(y, x),     p.GetOriginalColor(y, x),     p.GetOriginalColor(y, x + 1),
                      p.GetOriginalColor(y, x),     p.GetOriginalColor(y, x),     p.GetOriginalColor(y, x + 1),
                      p.GetOriginalColor(y + 1, x), p.GetOriginalColor(y + 1, x), p.GetOriginalColor(y + 1, x + 1)};
        } else if (x == w - 1) {  // последний столбец
            matrix = {p.GetOriginalColor(y, x - 1),     p.GetOriginalColor(y, x),     p.GetOriginalColor(y, x),
                      p.GetOriginalColor(y, x - 1),     p.GetOriginalColor(y, x),     p.GetOriginalColor(y, x),
                      p.GetOriginalColor(y + 1, x - 1), p.GetOriginalColor(y + 1, x), p.GetOriginalColor(y + 1, x)};
        } else {
            matrix = {p.GetOriginalColor(y, x - 1),     p.GetOriginalColor(y, x),     p.GetOriginalColor(y, x + 1),
                      p.GetOriginalColor(y, x - 1),     p.GetOriginalColor(y, x),     p.GetOriginalColor(y, x + 1),
                      p.GetOriginalColor(y + 1, x - 1), p.GetOriginalColor(y + 1, x), p.GetOriginalColor(y + 1, x + 1)};
        }
    } else if (y == h - 1) {  // последняя строка
        if (x == 0) {         // первый столбец
            matrix = {p.GetOriginalColor(y - 1, x), p.GetOriginalColor(y - 1, x), p.GetOriginalColor(y - 1, x + 1),
                      p.GetOriginalColor(y, x),     p.GetOriginalColor(y, x),     p.GetOriginalColor(y, x + 1),
                      p.GetOriginalColor(y, x),     p.GetOriginalColor(y, x),     p.GetOriginalColor(y, x + 1)};
        } else if (x == w - 1) {  // последний столбец
            matrix = {p.GetOriginalColor(y - 1, x - 1), p.GetOriginalColor(y - 1, x), p.GetOriginalColor(y - 1, x),
                      p.GetOriginalColor(y, x - 1),     p.GetOriginalColor(y, x),     p.GetOriginalColor(y, x),
                      p.GetOriginalColor(y, x - 1),     p.GetOriginalColor(y, x),     p.GetOriginalColor(y, x)};
        } else {
            matrix = {p.GetOriginalColor(y - 1, x - 1), p.GetOriginalColor(y - 1, x), p.GetOriginalColor(y - 1, x + 1),
                      p.GetOriginalColor(y, x - 1),     p.GetOriginalColor(y, x),     p.GetOriginalColor(y, x + 1),
                      p.GetOriginalColor(y, x - 1),     p.GetOriginalColor(y, x),     p.GetOriginalColor(y, x + 1)};
        }
    } else {
        if (x == 0) {
            matrix = {p.GetOriginalColor(y - 1, x), p.GetOriginalColor(y - 1, x), p.GetOriginalColor(y - 1, x + 1),
                      p.GetOriginalColor(y, x),     p.GetOriginalColor(y, x),     p.GetOriginalColor(y, x + 1),
                      p.GetOriginalColor(y + 1, x), p.GetOriginalColor(y + 1, x), p.GetOriginalColor(y + 1, x + 1)};
        } else if (x == w - 1) {
            matrix = {p.GetOriginalColor(y - 1, x - 1), p.GetOriginalColor(y - 1, x), p.GetOriginalColor(y - 1, x),
                      p.GetOriginalColor(y, x - 1),     p.GetOriginalColor(y, x),     p.GetOriginalColor(y, x),
                      p.GetOriginalColor(y + 1, x),     p.GetOriginalColor(y + 1, x), p.GetOriginalColor(y + 1, x)};
        } else {
            matrix = {p.GetOriginalColor(y - 1, x - 1), p.GetOriginalColor(y - 1, x), p.GetOriginalColor(y - 1, x + 1),
                      p.GetOriginalColor(y, x - 1),     p.GetOriginalColor(y, x),     p.GetOriginalColor(y, x + 1),
                      p.GetOriginalColor(y + 1, x - 1), p.GetOriginalColor(y + 1, x), p.GetOriginalColor(y + 1, x + 1)};
        }
    }
    return matrix;
}

void Sharp::ApplyFilter(Picture &p) {
    p.SetOriginal();
    const unsigned int h = p.GetHeight();
    const unsigned int w = p.GetWidth();
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            Color new_color;
            std::vector<Color> neighbours = GetNeighbours(p, y, x);
            for (int i = 0; i < neighbours.size(); ++i) {
                new_color.r += matrix_[i] * neighbours[i].r;
                new_color.g += matrix_[i] * neighbours[i].g;
                new_color.b += matrix_[i] * neighbours[i].b;
            }
            new_color.r = std::min(1.0, std::max(0.0, new_color.r));
            new_color.g = std::min(1.0, std::max(0.0, new_color.g));
            new_color.b = std::min(1.0, std::max(0.0, new_color.b));
            p.SetColor(y, x, new_color);
        }
    }
    p.SetOriginal();
}

EdgeDetection::EdgeDetection(Grayscale gs, Picture &p, double threshold) {
    threshold_ = threshold;
    gs.ApplyFilter(p);
}

void EdgeDetection::ApplyFilter(Picture &p) {
    p.SetOriginal();
    const unsigned int h = p.GetHeight();
    const unsigned int w = p.GetWidth();
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            Color new_color;
            std::vector<Color> neighbours = GetNeighbours(p, y, x);
            for (int i = 0; i < neighbours.size(); ++i) {
                new_color.r += matrix_[i] * neighbours[i].r;
            }
            new_color.r = std::min(1.0, std::max(0.0, new_color.r));
            if (new_color.r - threshold_ > D) {
                new_color = {1.0f, 1.0f, 1.0f};
            } else {
                new_color = {0.0f, 0.0f, 0.0f};
            }
            p.SetColor(y, x, new_color);
        }
    }
    p.SetOriginal();
}
