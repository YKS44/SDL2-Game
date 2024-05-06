#pragma once

#include <SDL2/SDL.h>
#include "types.h"
#include "arraylist.h"
#include "vector.h"
#include "rect.h"

typedef struct{
    SDL_Window* window;
    SDL_Renderer* renderer;
    ArrayList* entity_list;
    ArrayList* tile_list;
    //TODO: particle list, background list, etc
} Rendering;

typedef struct{
    Rect rect; //TODO change to pose. I want to only render with the position and the texture. top left would be the position. width would go fully right and height would go fully left in rect.
    u8 rgba[]; //TODO change to texture
} RenderData;

void render_init(void);
void render_periodic(void);