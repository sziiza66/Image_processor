
#ifndef IMG_PROC_COLUTILSC_H
#define IMG_PROC_COLUTILSC_H

#include <cstdint>
#include <functional>

#include "../color.h"

namespace gradient {

const extern std::function<double(const Rgb<uint8_t>&)> SUMM_MAPPING;

const extern std::function<double(const Rgb<uint8_t>&)> LEX_MAPPING;

const extern std::function<double(const Rgb<uint8_t>&)> LEX_CUTOFF_MAPPING;

}  // namespace gradient

#endif  // IMG_PROC_COLUTILSC_H
