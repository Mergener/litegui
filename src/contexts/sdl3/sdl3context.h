#ifndef LITEGUI_SDL3CONTEXT_H
#define LITEGUI_SDL3CONTEXT_H

#include "../../context.h"

#include <SDL3/SDL.h>

namespace litegui {

class SDL3RenderContext : public RenderContext {
public:
    [[nodiscard]] virtual Color color() const = 0;
    virtual void set_color(Color c) = 0;
    [[nodiscard]] virtual Color bg_color() const = 0;
    virtual void set_bg_color(Color c) = 0;
    [[nodiscard]] virtual Rect size() const = 0;

    virtual void draw_point(const Point& point) = 0;
    virtual void draw_rect(const Rect& rect) = 0;

    /**
     * Constructs a SDL3 render context from a pre-initialized SDL Renderer.
     *
     * Important: it's the caller's responsibility to manage the lifetime of the
     * renderer -- including keeping it alive for the duration of the SDL3Context
     * and cleaning it up when not used anymore.
     * @param renderer
     */
    explicit SDL3RenderContext(SDL_Renderer* renderer);

private:
    SDL_Renderer* m_renderer;
    Color m_bg_color {};
};



class SDL3Context : public SDL3RenderContext {
public:
    explicit SDL3Context(SDL_Renderer* renderer);
};

} // litegui

#endif //SDL3CONTEXT_H
