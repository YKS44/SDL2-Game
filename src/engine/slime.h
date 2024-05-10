#pragma once

#include "vector.h"
#include "arraylist.h"

typedef struct {
    Vec2 point;
    Vec2 prevPoint;
} Point;

typedef struct {
    u32 idx1;
    u32 idx2;
    u32 length;
} Line;

typedef struct {
    ArrayList* points;
    ArrayList* lines;
    f32 elasticity;
} Slime;

void slime_update(Slime* slime);
void slime_destroy(Slime* slime);
void slime_render(Slime slime);
Slime* slime_create(i32 pts[][2], u32 connections[][2], i32 scale, f32 elasticity);