
#ifndef IMG_PROC_BASICFILTERPRODUCERS_H
#define IMG_PROC_BASICFILTERPRODUCERS_H

#include "../filters/allfilters.h"
#include "filterdescriptor.h"

using PFitlerProducer = Filter* (*)(const FilterDescriptor& fd);

Filter* CropFilterProducer(const FilterDescriptor& fd);
Filter* GrayscaleFilterProducer(const FilterDescriptor& fd);
Filter* NegativeFilterProducer(const FilterDescriptor& fd);
Filter* SharpeningFilterProducer(const FilterDescriptor& fd);
Filter* EdgeDetectionFilterProducer(const FilterDescriptor& fd);
Filter* GaussianBlurFilterProducer(const FilterDescriptor& fd);
Filter* AmusingFilterProducer(const FilterDescriptor& fd);

#endif  // IMG_PROC_BASICFILTERPRODUCERS_H
