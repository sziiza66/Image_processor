
#include "filterfactory.h"

namespace {

const std::map<std::string, PFitlerProducer> BASIC_PRODUCERS = {
    {"crop", CropFilterProducer},        {"gs", GrayscaleFilterProducer},       {"neg", NegativeFilterProducer},
    {"sharp", SharpeningFilterProducer}, {"edge", EdgeDetectionFilterProducer}, {"blur", GaussianBlurFilterProducer}};

}  // namespace

FilterFactory::FilterFactory() : producers_(BASIC_PRODUCERS) {
}

void FilterFactory::SetPFilterProducer(const std::string& fname, PFitlerProducer prod) {
    producers_[fname] = prod;
}

FilterPipeline FilterFactory::MakeFilterPipeline(const std::vector<FilterDescriptor>& fds) const {
    FilterPipeline fp;
    for (const FilterDescriptor& fd : fds) {
        Filter* nf = MakeFilter(fd);
        if (!nf) {
            throw std::runtime_error(
                "Can't create filter \"" + std::string(fd.GetFilterName()) +
                "\" with specifid parameters. There may be no filter with this name or parameters are invalid.");
        }
        fp.AddFilter(nf);
    }
    return fp;
}

Filter* FilterFactory::MakeFilter(const FilterDescriptor& fd) const {
    std::string fname = std::string(fd.GetFilterName());
    auto iter = producers_.find(fname);
    if (iter == producers_.end()) {
        return nullptr;
    }
    return iter->second(fd);
}
