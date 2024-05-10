#pragma once

#include "render.h"
#include "timer.h"

typedef struct{
    Rendering rendering;

    i32 mouseX;
    i32 mouseY;

    TimeState timeState;
} Global;

extern Global global;