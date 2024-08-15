
#ifndef IMG_PROC_BITMAP_H
#define IMG_PROC_BITMAP_H

#include <algorithm>
#include <functional>
#include <stdexcept>
#include <vector>

#include "../color.h"

template <typename COL>
class Bitmap {
public:
    using Matrix = std::vector<std::vector<COL>>;

    Bitmap() : bitmap_(0) {
    }

    Bitmap(size_t height, size_t width, COL def = COL()) : bitmap_(height, std::vector<COL>(width, def)) {
        if (!IsValidResoltion(height, width)) {
            throw std::invalid_argument(
                "You are trying to create Bitmap with 0 rows and more than 0 coloumns or vice versa.");
        }
    }

    Bitmap(const Bitmap<COL>& other) : bitmap_(other.bitmap_) {
    }

    Bitmap(const Bitmap<COL>&& other) : bitmap_(std::move(other.bitmap_)) {
    }

    ~Bitmap() {
    }

    Bitmap& operator=(const Bitmap<COL>& other) {
        bitmap_ = other.bitmap_;
        return *this;
    }

    Bitmap& operator=(const Bitmap<COL>&& other) {
        bitmap_ = std::move(other.bitmap_);
        return *this;
    }

    const Matrix& GetContainer() const {
        return bitmap_;
    }

    size_t GetHeight() const {
        return bitmap_.size();
    }

    size_t GetWidth() const {
        if (bitmap_.empty()) {
            return 0;
        }
        return bitmap_[0].size();
    }

    void SetHeight(size_t height, COL def = COL()) {
        if (height == 0 && !bitmap_.empty() && !bitmap_[0].empty()) {
            throw std::invalid_argument(
                "You are trying ot set height to 0, when wigth is non-zero, use SetResolution(0, 0) instead.");
        }
        bitmap_.resize(height, std::vector<COL>(bitmap_[0].size(), def));
    }

    void SetWidth(size_t width, COL def = COL()) {
        if (width == 0 && !bitmap_.empty()) {
            throw std::invalid_argument(
                "You are trying ot set width to 0, when height is non-zero, use SetResolution(0, 0) instead.");
        }
        for (std::vector<COL>& row : bitmap_) {
            row.resize(width, def);
        }
    }

    void SetResolution(size_t height, size_t width, COL def = COL()) {
        if (height == 0 && width == 0) {
            bitmap_.clear();
            return;
        }
        if (!IsValidResoltion(height, width)) {
            throw std::invalid_argument("You are trying to create Bitmap with 0 rows or 0 columns.");
        }
        SetWidth(width);
        SetHeight(height);
    }

    COL At(size_t i, size_t j) const {
        try {
            return bitmap_.at(i).at(j);
        } catch (const std::out_of_range& e) {
            throw std::out_of_range("Element with this index doesn't exist.");
        }
    }

    COL& At(size_t i, size_t j) {
        try {
            return bitmap_.at(i).at(j);
        } catch (const std::out_of_range& e) {
            throw std::out_of_range("Element with this index doesn't exist.");
        }
    }

    void SetColorAt(size_t i, size_t j, COL newcol) {
        At(i, j) = newcol;
    }

    void Swap(Bitmap<COL>& other) noexcept {
        std::swap(bitmap_, other.bitmap_);  // Должно работать за константу.
    }

    void ReverseHorisontally() {
        for (size_t i = 0; i < bitmap_.size(); ++i) {
            bitmap_.reserve();
        }
    }

    void SortHorisontally(const std::function<bool(const COL&, const COL&)>& srt, bool rev) {
        for (size_t i = 0; i < GetHeight(); ++i) {
            if (rev) {
                std::sort(bitmap_[i].rbegin(), bitmap_[i].rend(), srt);
            } else {
                std::sort(bitmap_[i].begin(), bitmap_[i].end(), srt);
            }
        }
    }

    Bitmap<COL> GetRotated(bool clockwise = true) const {
        if (bitmap_.empty()) {
            return Bitmap<COL>(0, 0);
        }
        Bitmap<COL> res(GetWidth(), GetHeight());
        for (size_t i = 0; i < res.GetHeight(); ++i) {
            for (size_t j = 0; j < res.GetWidth(); ++j) {
                size_t ni = clockwise ? i : res.GetHeight() - i - 1;
                size_t nj = clockwise ? j : res.GetWidth() - j - 1;
                res.At(i, j) = bitmap_[nj][ni];
            }
        }
        return res;
    }

private:
    bool IsValidResoltion(size_t height, size_t width) {
        return !(width == 0 && height != 0) && !(width != 0 && height == 0);
    }

    Matrix bitmap_;
};

#endif  // IMG_PROC_BITMAP_H
