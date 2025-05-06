// Sample source file based off of https://wiki.libsdl.org/SDL3/README/main-functions

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <iostream>

#define USE_SDL3
#include "litegui.h"
using namespace litegui;

struct AppContext {
    SDL_Renderer* renderer = nullptr;
    SDL_Window* window = nullptr;
    std::unique_ptr<SDL3RenderContext> render_ctx;
};

/** Called on program initialization. */
SDL_AppResult SDL_AppInit(void** app_state, int argc, char* argv[]) {
    auto* context = new AppContext();
    *app_state = context;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("litegui", 640, 480, 0, &context->window, &context->renderer)) {
        SDL_Log("Failed to create window or renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    context->render_ctx = std::make_unique<SDL3RenderContext>(context->renderer);

    return SDL_APP_CONTINUE;
}

/** Called repeatedly every frame. Run update logic here. */
SDL_AppResult SDL_AppIterate(void *app_state) {
    AppContext* ctx = static_cast<AppContext*>(app_state);

    ctx->render_ctx->set_color(Color::ORANGE);
    ctx->render_ctx->clear();
    ctx->render_ctx->render_present();

    return SDL_APP_CONTINUE;
}

/** Handle app events here. */
SDL_AppResult SDL_AppEvent(void* app_state, SDL_Event* ev) {
    AppContext* ctx = static_cast<AppContext*>(app_state);
    if (ev->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

/** Runs on program exit. */
void SDL_AppQuit(void* app_state, SDL_AppResult res) {
}