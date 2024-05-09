#pragma once

#include "render.h"

typedef struct{
    Rendering rendering;
    i32 mouseX;
    i32 mouseY;
} Global;

extern Global global;