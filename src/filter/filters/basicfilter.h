
#ifndef IMG_PROC_BASICFILTER_H
#define IMG_PROC_BASICFILTER_H

#include <cstdint>

#include "../../color/bitmap/bitmap.h"
#include "../../bmp/bmp.h"

using RGB24 = Bmp24::RGB24;

class Filter {
public:
    virtual ~Filter() = default;

public:
    virtual void ApplyOnBmp(Bmp24& image) const = 0;

protected:
    virtual void CheckParams() const = 0;

private:
};

class CropFilter : public Filter {
public:
    CropFilter(size_t height, size_t width) : height_(width == 0 ? 0 : height), width_(height == 0 ? 0 : width) {
        CheckParams();
    }

    ~CropFilter() override {
    }

public:
    void ApplyOnBmp(Bmp24& image) const override;

private:
    void CheckParams() const override;

private:
    size_t height_;
    size_t width_;
};

class GrayscaleFilter : virtual public Filter {
public:
    GrayscaleFilter() {
    }

    ~GrayscaleFilter() override {
    }

public:
    void ApplyOnBmp(Bmp24& image) const override;

private:
    void CheckParams() const override{};
};

class NegativeFilter : public Filter {
public:
    NegativeFilter() {
    }

    ~NegativeFilter() override {
    }

public:
    void ApplyOnBmp(Bmp24& image) const override;

private:
    void CheckParams() const override{};
};

class GaussianBlurFilter : public Filter {
public:
    explicit GaussianBlurFilter(double sigma) : sigma_(sigma) {
        CheckParams();
    }

    ~GaussianBlurFilter() override {
    }

public:
    void ApplyOnBmp(Bmp24& image) const override;

private:
    void CheckParams() const override;

private:
    double sigma_;
};

#endif  // IMG_PROC_BASICFILTER_H
