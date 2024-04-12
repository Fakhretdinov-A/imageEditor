#pragma once
#include "standard_filters.h"

class RotatePicture : public Filter {
    double angle_;

public:
    explicit RotatePicture(double);
    void ApplyFilter(Picture &) override;
};

class Minecraft : public Filter {
public:
    void ApplyFilter(Picture &) override;
};

class Glass : public Filter {
protected:
    const double pm = 2.00;
    double param1 = p1;
    int param2 = p2;

public:
    void ApplyFilter(Picture &) override;
};

class Strange1 : public Glass {
public:
    void ApplyFilter(Picture &) override;
};

class Strange2 : public Glass {
public:
    void ApplyFilter(Picture &) override;
};
