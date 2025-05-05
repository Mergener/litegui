// Sample source file based off of https://wiki.libsdl.org/SDL3/README/main-functions

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <iostream>

struct AppContext {
    SDL_Renderer* renderer = nullptr;
    SDL_Window* window = nullptr;
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

    return SDL_APP_CONTINUE;
}

/** Called repeatedly every frame. Run update logic here. */
SDL_AppResult SDL_AppIterate(void *app_state) {
    return SDL_APP_CONTINUE;
}

/** Handle app events here. */
SDL_AppResult SDL_AppEvent(void* app_state, SDL_Event* ev) {
    if (ev->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

/** Runs on program exit. */
void SDL_AppQuit(void* app_state, SDL_AppResult res) {
}