
#include "amusingfilter.h"

#include "../../color/color_util/colutils.h"

const std::function<bool(const RGB24&, const RGB24&)> AmusingFilter::AMUSING_SRT = [](const RGB24& col1,
                                                                                      const RGB24& col2) {
    return gradient::LEX_CUTOFF_MAPPING(col1) < gradient::LEX_CUTOFF_MAPPING(col2);
};
