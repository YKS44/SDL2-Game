#pragma once

#include "vector.h"
#include <stdbool.h>
#include "arraylist.h"

typedef struct {
    Vec2 point;
    Vec2 prevPoint;
    bool locked;
} Point;

typedef struct {
    u32 idx1;
    u32 idx2;
    u32 length;
} Line;

typedef struct Slime{
    ArrayList* points;
    ArrayList* lines;
} Slime;

extern Slime player;

void slime_init();
void slime_periodic();