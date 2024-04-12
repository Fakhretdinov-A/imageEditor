#pragma once
#include "../bmppicture.h"
#include <cmath>
#include <algorithm>
#include <random>

class Filter {
protected:
    const double p1 = 16.0;
    const int p2 = 50;

public:
    virtual void ApplyFilter(Picture &) = 0;
    ~Filter() = default;
};

class Grayscale : public Filter {
public:
    void ApplyFilter(Picture &) override;
};

class Negative : public Filter {
public:
    void ApplyFilter(Picture &) override;
};

class Crop : public Filter {
    int width_;
    int height_;

public:
    void ApplyFilter(Picture &) override;
    Crop(int, int);
};

class GaussianBlur : public Filter {
    std::vector<double> params_;

public:
    explicit GaussianBlur(double);
    void ApplyFilter(Picture &) override;
};
