#ifndef LITEGUI_TYPES_H
#define LITEGUI_TYPES_H

#include <cstdint>

namespace litegui {

struct Point {
    int x;
    int y;

    Point() = default;
    constexpr Point(int x, int y);
};

inline constexpr Point::Point(int x, int y)
    : x(x), y(y) { }

struct Rect {
    int x;
    int y;
    int w;
    int h;

    Rect() = default;
    constexpr Rect(int x, int y, int w, int h);
};

inline constexpr Rect::Rect(int x, int y, int w, int h)
    : x(x), y(y), w(w), h(h) { }

struct Color {
    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;
    std::uint8_t a;

    Color() = default;
    constexpr Color(std::uint8_t r,
                    std::uint8_t g,
                    std::uint8_t b,
                    std::uint8_t a = 255);
};

inline constexpr Color::Color(std::uint8_t r,
                              std::uint8_t g,
                              std::uint8_t b,
                              std::uint8_t a)
    : r(r), g(g), b(b), a(a) { }

} // litegui

#endif // LITEGUI_TYPES_H
