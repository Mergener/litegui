#ifndef LITEGUI_WIDGET_H
#define LITEGUI_WIDGET_H

#include <stdexcept>

namespace litegui {

struct WidgetContext {
    RenderContext* render_context = nullptr;
    EventContext* event_context = nullptr;
};

template <typename T>
class Widget {
public:
    const WidgetContext& context() const {
        return m_ctx;
    }

    Widget(WidgetContext ctx)
        : m_ctx(ctx) {
        if (ctx.event_context == nullptr) {
            throw std::runtime_error("Missing event context in widget context.");
        }
        if (ctx.render_context == nullptr) {
            throw std::runtime_error("Missing render context in widget context.");
        }
    }

private:
    WidgetContext m_ctx;
};

} // litegui

#endif // LITEGUI_WIDGET_H
