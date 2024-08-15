
#ifndef IMG_PROC_FILTERPIPELINE_H
#define IMG_PROC_FILTERPIPELINE_H

#include <vector>

#include "../filters/allfilters.h"

class FilterPipeline {
public:
    FilterPipeline() {
    }

    ~FilterPipeline();

public:
    void AddFilter(Filter* f) {
        filters_.push_back(f);
    }

    size_t Size() const {
        return filters_.size();
    }

    void ApplyOnBmp(Bmp24& image) const;

private:
    std::vector<Filter*> filters_;
};

#endif  // IMG_PROC_FILTERPIPELINE_H
