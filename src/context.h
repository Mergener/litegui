#ifndef CONTEXT_H
#define CONTEXT_H

#include "event.h"
#include "types.h"

#include <mutex>
#include <deque>
#include <functional>

namespace litegui {

class RenderContext {
public:
    [[nodiscard]] virtual Color color() const = 0;
    virtual void set_color(Color c) = 0;
    [[nodiscard]] virtual Rect size() const = 0;

    virtual void draw_point(const Point& point) = 0;
    virtual void draw_rect(const Rect& rect) = 0;

    virtual ~RenderContext() = default;
};

struct ClickEvent {
    Point point;
};

class EventContext {
    Event<ClickEvent>& click_event();
    Event<ClickEvent>& release_event();

protected:
    struct CallableEventContext {
        CallableEvent<ClickEvent> click;
        CallableEvent<ClickEvent> release;
    };
    CallableEventContext& callable_events();

private:
    CallableEventContext m_events;
};

} // litegui

#endif //CONTEXT_H
