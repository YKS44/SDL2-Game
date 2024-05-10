#pragma once

#include <SDL2/SDL.h>
#include "types.h"
#include "arraylist.h"
#include "vector.h"
#include "rect.h"

typedef struct{
    SDL_Window* window;
    SDL_Renderer* renderer;
    ArrayList* render_entity_list;
    ArrayList* tile_list;
    //TODO: particle list, background list, etc
} Rendering;

void render_init(void);
void render_periodic(void);