#ifndef CONTEXT_H
#define CONTEXT_H

#include "types.h"

#include <mutex>
#include <deque>
#include <functional>

namespace litegui {

class RenderContext {
public:
    [[nodiscard]] virtual Color color() const = 0;
    virtual void set_color(Color c) = 0;
    [[nodiscard]] virtual Color bg_color() const = 0;
    virtual void set_bg_color(Color c) = 0;
    [[nodiscard]] virtual Rect size() const = 0;

    virtual void draw_point(const Point& point) = 0;
    virtual void draw_rect(const Rect& rect) = 0;

    virtual ~RenderContext() = default;
};

class EventContext {
public:

    virtual ~EventContext() = default;
};

} // litegui

#endif //CONTEXT_H
