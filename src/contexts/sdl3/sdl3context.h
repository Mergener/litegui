#ifndef LITEGUI_SDL3CONTEXT_H
#define LITEGUI_SDL3CONTEXT_H

#include "../../context.h"

#include <SDL3/SDL.h>

namespace litegui {

class SDL3RenderContext : public RenderContext {
public:
    [[nodiscard]] Color color() const override;
    void set_color(Color c) override;
    [[nodiscard]] virtual Rect size() const override;

    void draw_point(const Point& point) override;
    void draw_rect(const Rect& rect) override;

    void render_present();
    void clear();

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
};

class SDL3EventContext : public EventContext {
public:
    SDL_AppResult handle_sdl_event(const SDL_Event& ev);
};

} // litegui

#endif //SDL3CONTEXT_H
