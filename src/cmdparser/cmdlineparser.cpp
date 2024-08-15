
#include "cmdlineparser.h"

#include <stdexcept>

CmdLineParser::CmdLineParser(size_t argc, const char* const* const argv)
    : input_file_(argc > 1 ? argv[1] : ""), output_file_(argc > 2 ? argv[2] : "") {
    for (size_t i = 3; i < argc; ++i) {
        if (argv[i][0] == '-') {
            filters_.emplace_back(std::string_view(argv[i] + 1));
        } else {
            if (filters_.empty()) {
                throw std::runtime_error("You can't specify parameters to not specified filter.");
            }
            filters_.back().AddParam(argv[i]);
        }
    }
}
