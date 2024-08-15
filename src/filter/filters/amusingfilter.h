
#ifndef IMG_PROC_AMUSINGFILTER_H
#define IMG_PROC_AMUSINGFILTER_H

#include "sortfilter.h"

class AmusingFilter : public SortFilter {
public:
    AmusingFilter(bool vert, bool rev) : SortFilter(AMUSING_SRT, vert, rev) {
    }

    ~AmusingFilter() override {
    }

private:
    void CheckParams() const override{};

private:
    const static std::function<bool(const RGB24&, const RGB24&)> AMUSING_SRT;
};

#endif  // IMG_PROC_AMUSINGFILTER_H
