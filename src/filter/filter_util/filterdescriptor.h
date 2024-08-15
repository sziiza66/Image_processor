
#ifndef IMG_PROC_FILTERDESCRIPTOR_H
#define IMG_PROC_FILTERDESCRIPTOR_H

#include <vector>
#include <string>

class FilterDescriptor {
public:
    explicit FilterDescriptor(std::string_view filter) : filter_(filter) {
    }

    FilterDescriptor(std::string_view filter, const std::vector<std::string_view>& params)
        : filter_(filter), params_(params) {
    }

    void AddParam(std::string_view param) {
        params_.push_back(param);
    }

    std::string_view GetFilterName() const {
        return filter_;
    }

    const std::vector<std::string_view>& GetFilterParams() const {
        return params_;
    }

private:
    std::string_view filter_;
    std::vector<std::string_view> params_;
};

#endif  // IMG_PROC_FILTERDESCRIPTOR_H
