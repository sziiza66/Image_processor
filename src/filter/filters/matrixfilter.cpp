
#include "matrixfilter.h"

namespace {

constexpr int32_t Five = 5;

constexpr uint8_t ColConst = 255;

}  // namespace

void MatrixFilter::ApplyOnBmp(Bmp24& image) const {
    Bitmap<RGB24> buffer(image.GetBitmap());
    int64_t ver_offset = static_cast<int64_t>(matrix_.size()) / 2;
    int64_t hor_offset = static_cast<int64_t>(matrix_[0].size()) / 2;
    for (int64_t i = 0; i < buffer.GetHeight(); ++i) {
        for (int64_t j = 0; j < buffer.GetWidth(); ++j) {
            Rgb<int64_t> newcolor;
            for (int64_t k = i - ver_offset; k <= i + ver_offset; ++k) {
                for (int64_t p = j - hor_offset; p <= j + ver_offset; ++p) {
                    int64_t ver_nearest =
                        MinMax<int64_t>(k, static_cast<int64_t>(0), static_cast<int64_t>(buffer.GetHeight() - 1));
                    int64_t hor_nearest =
                        MinMax<int64_t>(p, static_cast<int64_t>(0), static_cast<int64_t>(buffer.GetWidth() - 1));
                    newcolor += matrix_[k + ver_offset - i][p + hor_offset - j] *
                                image.GetBitmap().At(ver_nearest, hor_nearest);
                }
            }
            newcolor.MinMaxCol(static_cast<int64_t>(0), static_cast<int64_t>(ColConst));
            buffer.At(i, j) = newcolor;
        }
    }
    image.SwapBitmap(buffer);
}

void MatrixFilter::CheckParams() const {
    if (matrix_.empty()) {
        throw std::invalid_argument("You can't create MatrixFilter with empty matrix.");
    }
    if (matrix_.size() % 2 == 0 || matrix_[0].size() % 2 == 0) {
        throw std::invalid_argument("You can't create MatrixFilter with even-sided matrix.");
    }
}

void EdgeDetectionFilter::ApplyOnBmp(Bmp24& image) const {
    GrayscaleFilter::ApplyOnBmp(image);
    MatrixFilter::ApplyOnBmp(image);
    Bitmap<RGB24> buffer(image.GetBitmap());
    for (int64_t i = 0; i < buffer.GetHeight(); ++i) {
        for (int64_t j = 0; j < buffer.GetWidth(); ++j) {
            RGB24& pixel = buffer.At(i, j);
            pixel = pixel.r > ColConst * threshold_ ? RGB24{ColConst, ColConst, ColConst} : RGB24{0, 0, 0};
        }
    }
    image.SwapBitmap(buffer);
}

const Matrix EdgeDetectionFilter::EDGE_DETECTION_MATRIX = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};

const Matrix SharpeningFilter::SHARPENING_MATRIX = {{0, -1, 0}, {-1, Five, -1}, {0, -1, 0}};
