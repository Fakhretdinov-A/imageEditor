#pragma once

#include "standard_filters.h"

std::vector<Color> GetNeighbours(Picture &, int, int);

class MatrixFilter : public Filter {
    std::vector<double> matrix_;
};

class Sharp : public MatrixFilter {
    const double sharp_coef_ = 5.0f;
    std::vector<double> matrix_ = {0.0f, -1.0f, 0.0f, -1.0f, sharp_coef_, -1.0f, 0.0f, -1.0f, 0.0f};

public:
    void ApplyFilter(Picture &) override;
};

class EdgeDetection : public MatrixFilter, public Grayscale {
    const double edge_detection_coef_ = 4.0f;
    std::vector<double> matrix_ = {0.0f, -1.0f, 0.0f, -1.0f, edge_detection_coef_, -1.0f, 0.0f, -1.0f, 0.0f};
    double threshold_;

public:
    EdgeDetection(Grayscale, Picture &, double);
    void ApplyFilter(Picture &) override;
};
