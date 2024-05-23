#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "arraylist.h"

typedef struct{
    bool pressed;
    bool held;
    bool released;
} Key;

extern Key KEYS[322];
extern ArrayList* instantKey;

void keyboard_init();
void keyboard_update_justPressed();