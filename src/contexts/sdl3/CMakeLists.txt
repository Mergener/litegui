add_library(ctx_sdl3 STATIC sdl3context.cpp sdl3context.h)
target_include_directories(ctx_sdl3 PRIVATE ${EXT_DIRECTORY}/sdl/include)