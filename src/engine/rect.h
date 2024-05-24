#pragma once

#include "vector.h"
#include "types.h"
#include <stdbool.h>
#include "slime.h"

typedef struct {
    Vec2 pos;
    u32 w;
    u32 h;
} Rect;

Rect rect_minkowski_diff(Rect rect1, Rect rect2);

//Calculate the penetration vector given the minkowski difference rect.
Vec2 rect_push_vec(Rect rect);

Hit rect_intersect_ray(Rect rect, Vec2 startPos, Vec2 velocity);
bool rect_intersect_point(Rect rect, Point point);
Rect rect_size_sum(Rect rect1, Rect rect2);
Vec2 rect_get_midpoint(Rect rect);