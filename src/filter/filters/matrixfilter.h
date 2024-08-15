
#ifndef IMG_PROC_MATRIXFILTER_H
#define IMG_PROC_MATRIXFILTER_H

#include <vector>

#include "basicfilter.h"

using Matrix = std::vector<std::vector<int32_t>>;

class MatrixFilter : virtual public Filter {
public:
    explicit MatrixFilter(const Matrix& matrix) : matrix_(matrix) {
        CheckParams();
    }

    ~MatrixFilter() override {
    }

public:
    void ApplyOnBmp(Bmp24& image) const override;

private:
    void CheckParams() const override;

private:
    Matrix matrix_;
};

class SharpeningFilter : public MatrixFilter {
public:
    SharpeningFilter() : MatrixFilter(SHARPENING_MATRIX) {
    }

private:
    const static Matrix SHARPENING_MATRIX;
};

class EdgeDetectionFilter : public MatrixFilter, public GrayscaleFilter {
public:
    explicit EdgeDetectionFilter(double threshold) : MatrixFilter(EDGE_DETECTION_MATRIX), threshold_(threshold) {
    }

public:
    void ApplyOnBmp(Bmp24& image) const override;

private:
    void CheckParams() const override {
    }

private:
    double threshold_;
    const static Matrix EDGE_DETECTION_MATRIX;
};

#endif  // IMG_PROC_MATRIXFILTER_H
