#pragma once

#include "types.h"

#define TIME global.timeState

typedef struct{
    f32 deltaTime;

    u64 now;
    u64 prev;

    //How much to delay the each loop by to have a fixed framerate. In milliseconds.
    u32 loopDelay;
} TimeState;

void time_init();
void time_periodic();