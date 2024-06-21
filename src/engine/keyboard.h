#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "arraylist.h"

#define LEFT_MOUSE 322
#define MID_MOUSE 323
#define RIGHT_MOUSE 324

typedef struct{
    bool pressed;
    bool held;
    bool released;
    SDL_Keymod mod;
} Key;

extern Key KEYS[322 + 3];
//the modifer key pressed
extern SDL_Keymod keymod;
extern ArrayList* instantKey;

void keyboard_init();
void keyboard_update_instantKey();