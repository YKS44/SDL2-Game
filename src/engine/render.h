#pragma once

#include <SDL2/SDL.h>
#include "types.h"
#include "arraylist.h"
#include "vector.h"
#include "rect.h"

#define RED (RGBA) {.r = 255, .g = 0, .b = 0, .a = 255}
#define GREEN (RGBA) {.r = 0, .g = 255, .b = 0, .a = 255}
#define BLUE (RGBA) {.r = 0, .g = 0, .b = 255, .a = 255}

typedef struct{
    SDL_Window* window;
    SDL_Renderer* renderer;
} Rendering;

typedef struct{
    u32 r;
    u32 g;
    u32 b;
    u32 a;
} RGBA;

void render_init(void);
void render_periodic(void);
void render_fill_rect(Rect rect, RGBA color);
void render_line(Vec2 p1, Vec2 p2, RGBA color);