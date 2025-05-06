#ifndef LITEGUI_TYPES_H
#define LITEGUI_TYPES_H

#include <limits>
#include <cstdint>
#include <type_traits>

namespace litegui {

template <typename T>
struct BasePoint {
    static_assert(std::is_arithmetic_v<T>);

    T x;
    T y;

    BasePoint() = default;
    constexpr BasePoint(T x, T y);
};

template <typename T>
inline constexpr BasePoint<T>::BasePoint(T x, T y)
    : x(x), y(y) { }

using Point = BasePoint<int>;
using FPoint = BasePoint<float>;
using FPoint64 = BasePoint<double>;

template <typename T>
struct BaseRect {
    static_assert(std::is_arithmetic_v<T>);

    T x;
    T y;
    T w;
    T h;

    BaseRect() = default;
    constexpr BaseRect(T x, T y, T w, T h);
};

template <typename T>
inline constexpr BaseRect<T>::BaseRect(T x, T y, T w, T h)
    : x(x), y(y), w(w), h(h) { }

using Rect = BaseRect<int>;
using FRect = BaseRect<float>;
using FRect64 = BaseRect<double>;

template <typename T>
struct BaseColor {
    static_assert(std::is_arithmetic_v<T>);

    static constexpr T MAX = std::is_floating_point_v<T>
                           ? static_cast<T>(1.0)
                           : static_cast<T>(std::numeric_limits<T>::max());

    T r;
    T g;
    T b;
    T a;

    constexpr BaseColor() = default;
    constexpr BaseColor(T r,
                        T g,
                        T b,
                        T a = MAX);

    static constexpr BaseColor RED { MAX, 0, 0 };
    static constexpr BaseColor GREEN { 0, MAX, 0 };
    static constexpr BaseColor BLUE { 0, 0, MAX };
    static constexpr BaseColor YELLOW { MAX, MAX, 0 };
    static constexpr BaseColor MAGENTA { MAX, 0, MAX };
    static constexpr BaseColor CYAN { 0, MAX, MAX };
    static constexpr BaseColor PURPLE { MAX / 4, 0, MAX / 2 };
    static constexpr BaseColor BROWN { MAX / 4, MAX / 4, 0 };
    static constexpr BaseColor TEAL { 0, MAX / 3, MAX / 3 };
    static constexpr BaseColor ORANGE { MAX, MAX / 2, 0 };
    static constexpr BaseColor BLACK { 0, 0, 0 };
    static constexpr BaseColor WHITE { MAX, MAX, MAX };
};

template <typename T>
inline constexpr BaseColor<T>::BaseColor(T r,
                                         T g,
                                         T b,
                                         T a)
    : r(r), g(g), b(b), a(a) { }

using Color = BaseColor<std::uint8_t>;
using FColor = BaseColor<float>;

} // litegui

#endif // LITEGUI_TYPES_H
