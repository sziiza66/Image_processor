
#include "filterpipeline.h"

FilterPipeline::~FilterPipeline() {
    for (Filter* f : filters_) {
        delete f;
    }
}

void FilterPipeline::ApplyOnBmp(Bmp24& image) const {
    for (Filter* f : filters_) {
        f->ApplyOnBmp(image);
    }
}
