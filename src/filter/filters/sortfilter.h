
#ifndef IMG_PROC_SORTFILTER_H
#define IMG_PROC_SORTFILTER_H

#include <functional>

#include "basicfilter.h"

class SortFilter : public Filter {
public:
    explicit SortFilter(const std::function<bool(const RGB24&, const RGB24&)>& srt, bool vert = false, bool rev = false)
        : sort_func_(srt), vertical_(vert), rev_(rev) {
    }

    ~SortFilter() override {
    }

public:
    void ApplyOnBmp(Bmp24& image) const override;

private:
    void CheckParams() const override{};

private:
    std::function<bool(const RGB24&, const RGB24&)> sort_func_;
    bool vertical_ = false;
    bool rev_ = false;
};

#endif  // IMG_PROC_SORTFILTER_H
