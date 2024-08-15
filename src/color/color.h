
#ifndef IMG_PROC_COLOR_H
#define IMG_PROC_COLOR_H

#include <cmath>
#include <type_traits>

template <typename T>
T MinMax(T val, T mi, T ma) {
    if (val > ma) {
        return ma;
    }
    if (val < mi) {
        return mi;
    }
    return val;
}

template <typename T>
struct Rgb {
public:
    static_assert(std::is_arithmetic_v<T>, "only arithmetic types are allowed.");

public:
    Rgb() : b(0), g(0), r(0) {
    }

    Rgb(T tr, T tg, T tb) : b(tb), g(tg), r(tr) {
    }

    ~Rgb() {
    }

public:
    template <typename S>
    explicit Rgb(const Rgb<S>& other) : b(other.b), g(other.g), r(other.r) {
    }

    template <typename S>
    Rgb<T>& operator=(const Rgb<S>& rhs) {
        r = static_cast<T>(rhs.r);
        g = static_cast<T>(rhs.g);
        b = static_cast<T>(rhs.b);
        return *this;
    }

    template <typename S>
    Rgb<T> operator*(S number) {
        return Rgb<T>(r * number, g * number, b * number);
    }

    template <typename S>
    Rgb<T>& operator+=(const Rgb<S>& rhs) {
        r += rhs.r;
        g += rhs.g;
        b += rhs.b;
        return *this;
    }

    template <typename S>
    Rgb<T>& operator*=(S rhs) {
        r *= rhs;
        g *= rhs;
        b *= rhs;
        return *this;
    }

public:
    void Round() {
        b = std::round(b);
        r = std::round(r);
        g = std::round(g);
    }

    void MinMaxCol(T mi, T ma) {
        b = MinMax(b, mi, ma);
        g = MinMax(g, mi, ma);
        r = MinMax(r, mi, ma);
    }

public:
    T b = 0;
    T g = 0;
    T r = 0;
} __attribute__((packed));

template <typename T, typename S>
Rgb<S> operator*(S lhs, const Rgb<T>& rhs) {
    return Rgb<S>(lhs * rhs.r, lhs * rhs.g, lhs * rhs.b);
}

#endif  // IMG_PROC_COLOR_H
