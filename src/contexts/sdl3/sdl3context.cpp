#include "sdl3context.h"

namespace litegui {

Color SDL3RenderContext::color() const {
    Color color;
    SDL_GetRenderDrawColor(m_renderer,
                           &color.r,
                           &color.g,
                           &color.b,
                           &color.a);
    return color;
}

void SDL3RenderContext::set_color(Color c) {
    SDL_SetRenderDrawColor(m_renderer, c.r, c.g, c.b, c.a);
}

Rect SDL3RenderContext::size() const {
    Rect rect {};
    SDL_GetRenderOutputSize(m_renderer, &rect.w, &rect.h);
    return rect;
}

void SDL3RenderContext::draw_point(const Point& point) {
    SDL_RenderPoint(m_renderer, point.x, point.y);
}

void SDL3RenderContext::draw_rect(const Rect& rect) {
    SDL_FRect f_rect {
        static_cast<float>(rect.x),
        static_cast<float>(rect.y),
        static_cast<float>(rect.w),
        static_cast<float>(rect.h)
    };
    SDL_RenderRect(m_renderer, &f_rect);
}

void SDL3RenderContext::render_present() {
    SDL_RenderPresent(m_renderer);
}

void SDL3RenderContext::clear() {
    SDL_RenderClear(m_renderer);
}

SDL3RenderContext::SDL3RenderContext(SDL_Renderer* renderer)
    : m_renderer(renderer) { }

} // litegui