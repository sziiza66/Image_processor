
#include "filterproducers.h"

#include <cmath>

namespace {

constexpr int Base10 = 10;

}  // namespace

Filter* CropFilterProducer(const FilterDescriptor& fd) {
    const auto par = fd.GetFilterParams();
    if (par.size() != 2) {
        return nullptr;
    }
    if (par[0].empty() || par[1].empty()) {
        return nullptr;
    }
    size_t width = std::strtoull(std::string(par[0]).c_str(), nullptr, Base10);
    size_t height = std::strtoull(std::string(par[1]).c_str(), nullptr, Base10);
    if (errno == ERANGE) {
        return nullptr;
    }
    if (width == 0 || height == 0) {
        return nullptr;
    }
    return new CropFilter(height, width);
}

Filter* GrayscaleFilterProducer(const FilterDescriptor& fd) {
    const auto par = fd.GetFilterParams();
    if (!par.empty()) {
        return nullptr;
    }
    return new GrayscaleFilter();
}
Filter* NegativeFilterProducer(const FilterDescriptor& fd) {
    const auto par = fd.GetFilterParams();
    if (!par.empty()) {
        return nullptr;
    }
    return new NegativeFilter();
}

Filter* SharpeningFilterProducer(const FilterDescriptor& fd) {
    const auto par = fd.GetFilterParams();
    if (!par.empty()) {
        return nullptr;
    }
    return new SharpeningFilter();
}

Filter* EdgeDetectionFilterProducer(const FilterDescriptor& fd) {
    const auto par = fd.GetFilterParams();
    if (par.size() != 1) {
        return nullptr;
    }
    if (par[0].empty()) {
        return nullptr;
    }
    double threshold = std::strtod(std::string(par[0]).c_str(), nullptr);
    if (errno == ERANGE || std::isnan(threshold) || std::isinf(threshold)) {
        return nullptr;
    }
    return new EdgeDetectionFilter(threshold);
}

Filter* GaussianBlurFilterProducer(const FilterDescriptor& fd) {
    const auto par = fd.GetFilterParams();
    if (par.size() != 1) {
        return nullptr;
    }
    if (par[0].empty()) {
        return nullptr;
    }
    std::string str_sigma = std::string(par[0]);
    double sigma = std::strtod(str_sigma.c_str(), nullptr);
    if (errno == ERANGE || std::isnan(sigma) || std::isinf(sigma) || sigma == 0) {
        return nullptr;
    }
    return new GaussianBlurFilter(sigma);
}

Filter* AmusingFilterProducer(const FilterDescriptor& fd) {
    const auto par = fd.GetFilterParams();
    if (par.size() != 2) {
        return nullptr;
    }
    for (size_t i = 0; i < 2; ++i) {
        if (par[i][0] != '0' && par[i][0] != '1') {
            return nullptr;
        }
    }
    bool vert = static_cast<bool>(par[0][0] - '0');
    bool rev = static_cast<bool>(par[1][0] - '0');
    return new AmusingFilter(vert, rev);
}
