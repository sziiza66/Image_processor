
#ifndef IMG_PROC_CMDLINEPARSER_H
#define IMG_PROC_CMDLINEPARSER_H

#include <vector>
#include <string>

#include "../filter/filter_util/filterdescriptor.h"

class CmdLineParser {
public:
    explicit CmdLineParser(size_t argc, const char* const* const argv);

    const std::string& GetInputFile() const {
        return input_file_;
    }

    const std::string& GetOutputFile() const {
        return output_file_;
    }

    const std::vector<FilterDescriptor>& GetFilters() {
        return filters_;
    }

    size_t GetFiltersCount() {
        return filters_.size();
    }

    const FilterDescriptor& GetFilterAt(size_t ind) {
        return filters_.at(ind);
    }

private:
    std::vector<FilterDescriptor> filters_ = {};
    std::string input_file_;
    std::string output_file_;
};

#endif  // IMG_PROC_CMDLINEPARSER_H
