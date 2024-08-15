
#include "colutils.h"

#include <cmath>

const std::function<double(const Rgb<uint8_t>&)> gradient::SUMM_MAPPING = [](const Rgb<uint8_t>& col) {
    return static_cast<double>(col.b + col.g + col.r);
};

const std::function<double(const Rgb<uint8_t>&)> gradient::LEX_MAPPING = [](const Rgb<uint8_t>& col) {
    constexpr double ColConst = 256;
    return ColConst * ColConst * col.r + ColConst * col.b + col.g;
};

const std::function<double(const Rgb<uint8_t>&)> gradient::LEX_CUTOFF_MAPPING = [](const Rgb<uint8_t>& col) {
    // Можно сделать это задаваемыми значениями для фильтра, но у меня нет времени,
    // в целом, подобрал дающие красивый результат константы (по крайней мере на Лене).
    constexpr double CutConst = 90;
    constexpr double DivConst = 1000000;
    return std::round((CutConst * CutConst * col.r + CutConst * col.b + col.g) / DivConst);
};
