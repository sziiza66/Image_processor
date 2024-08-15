
#include "basicfilter.h"

#include <cmath>
#include <numbers>

namespace {

constexpr uint8_t ColConst = 255;

}  // namespace

void CropFilter::ApplyOnBmp(Bmp24& image) const {
    size_t nheight = std::min(height_, image.GetBitmap().GetHeight());
    size_t nwidth = std::min(width_, image.GetBitmap().GetWidth());
    Bitmap<RGB24> buffer(nheight, nwidth);
    for (size_t i = 0; i < nheight; ++i) {
        for (size_t j = 0; j < nwidth; ++j) {
            buffer.At(i, j) = image.GetBitmap().At(i, j);
        }
    }
    image.SwapBitmap(buffer);
}

void CropFilter::CheckParams() const {
    if (width_ == 0 || height_ == 0) {
        throw std::invalid_argument(
            "You are trying to create CropFilter with width of 0 and height of more than 0 or vice versa.");
    }
}

void GrayscaleFilter::ApplyOnBmp(Bmp24& image) const {
    constexpr double Rc = 0.299l;
    constexpr double Gc = 0.587l;
    constexpr double Bc = 0.114l;
    Bitmap<RGB24> buffer(image.GetBitmap());
    for (size_t i = 0; i < buffer.GetHeight(); ++i) {
        for (size_t j = 0; j < buffer.GetWidth(); ++j) {
            auto& pixel = buffer.At(i, j);
            pixel.r = static_cast<typeof(pixel.r)>(Rc * pixel.r + Gc * pixel.g + Bc * pixel.b);
            pixel.b = pixel.r;
            pixel.g = pixel.r;
        }
    }
    image.SwapBitmap(buffer);
}

void NegativeFilter::ApplyOnBmp(Bmp24& image) const {
    Bitmap<RGB24> buffer(image.GetBitmap());
    for (size_t i = 0; i < buffer.GetHeight(); ++i) {
        for (size_t j = 0; j < buffer.GetWidth(); ++j) {
            auto& pixel = buffer.At(i, j);
            pixel.r = ColConst - pixel.r;
            pixel.g = ColConst - pixel.g;
            pixel.b = ColConst - pixel.b;
        }
    }
    image.SwapBitmap(buffer);
}

void GaussianBlurFilter::CheckParams() const {
    if (std::isinf(sigma_) || std::isnan(sigma_) || sigma_ == 0) {
        throw std::invalid_argument("Sigma parameter is ether 0 or invalid.");
    }
}

void GaussianBlurFilter::ApplyOnBmp(Bmp24& image) const {
    constexpr int GaussConst = 7;
    const int64_t area_const = static_cast<int64_t>(ceill(sigma_ * GaussConst));
    int64_t height = static_cast<int64_t>(image.GetBitmap().GetHeight());
    int64_t width = static_cast<int64_t>(image.GetBitmap().GetWidth());
    std::vector<std::vector<Rgb<double>>> matrix_step1(height, std::vector<Rgb<double>>(width));
    std::vector<std::vector<Rgb<double>>> matrix_step2(height, std::vector<Rgb<double>>(width));
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            matrix_step2[i][j] = image.GetBitmap().At(i, j);
            matrix_step2[i][j] *= 1.0 / ColConst;
        }
    }
    for (size_t i = 0; i < height; ++i) {
        for (int64_t j = 0; j < width; ++j) {
            int64_t left = j - area_const;
            int64_t right = j + area_const;
            for (int64_t p = left; p < right; ++p) {
                int64_t ind = p < 0 || p >= width ? j : p;
                matrix_step1[i][j] +=
                    matrix_step2[i][ind] * exp(static_cast<double>(-(j - p) * (j - p)) / (sigma_ * sigma_ * 2));
            }
        }
    }
    for (size_t i = 0; i < width; ++i) {
        for (int64_t j = 0; j < height; ++j) {
            int64_t left = j - area_const;
            int64_t right = j + area_const;
            matrix_step2[j][i] = Rgb<double>(0, 0, 0);
            for (int64_t p = left; p < right; ++p) {
                int64_t ind = p < 0 || p >= width ? j : p;
                matrix_step2[j][i] +=
                    matrix_step1[ind][i] * exp(static_cast<double>(-(j - p) * (j - p)) / (sigma_ * sigma_ * 2));
            }
        }
    }
    Bitmap<RGB24> buffer(height, width);
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            matrix_step2[i][j] *= 1.0 / (std::numbers::pi * sigma_ * sigma_ * 2);
            matrix_step2[i][j] *= ColConst;
            matrix_step2[i][j].Round();
            matrix_step2[i][j].MinMaxCol(0, ColConst);
            buffer.At(i, j) = matrix_step2[i][j];
        }
    }
    image.SwapBitmap(buffer);
}
