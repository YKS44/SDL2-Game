#pragma once

#include <stdbool.h>
#include "vector.h"
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

typedef struct {
    ArrayList* points;
    ArrayList* lines;
} Slime;

extern Slime player;

//Ranges from (0,1]. 1 is more snappy
extern const f32 elasticity;

void slime_init();
void slime_periodic();