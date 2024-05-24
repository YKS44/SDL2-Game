#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "arraylist.h"

typedef struct{
    bool pressed;
    bool held;
    bool released;
    SDL_Keymod mod;
} Key;

extern Key KEYS[322];
//the modifer key pressed
extern SDL_Keymod keymod;
extern ArrayList* instantKey;

void keyboard_init();
void keyboard_update_instantKey();