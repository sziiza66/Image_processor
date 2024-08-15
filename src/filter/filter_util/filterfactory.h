#ifndef IMG_PROC_FILTERFACTORY_H
#define IMG_PROC_FILTERFACTORY_H

#include <map>
#include "filterdescriptor.h"
#include "filterproducers.h"
#include "filterpipeline.h"

class FilterFactory {
public:
    FilterFactory();

    ~FilterFactory() {
    }

public:
    void SetPFilterProducer(const std::string& fname, PFitlerProducer prod);

    FilterPipeline MakeFilterPipeline(const std::vector<FilterDescriptor>& fds) const;

    Filter* MakeFilter(const FilterDescriptor& fd) const;

private:
    std::map<std::string, PFitlerProducer> producers_;
};

#endif  // IMG_PROC_FILTERFACTORY_H
