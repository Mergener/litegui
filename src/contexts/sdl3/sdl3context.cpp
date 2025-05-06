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

Color SDL3RenderContext::bg_color() const {
    return m_bg_color;
}

void SDL3RenderContext::set_bg_color(Color c) {

}

Rect SDL3RenderContext::size() const {

}

void SDL3RenderContext::draw_point(const Point& point) {

}

void SDL3RenderContext::draw_rect(const Rect& rect) {

}

SDL3RenderContext::SDL3RenderContext(SDL_Renderer* renderer)
    : m_renderer(renderer) { }

SDL3Context::SDL3Context(SDL_Renderer* renderer)
    : SDL3RenderContext(renderer) { }

} // litegui