#pragma once

#include "types.h"
#include <stdbool.h>

typedef struct {
    f32 x;
    f32 y;
} Vec2;

typedef struct {
    bool is_hit;
    Vec2 pos;
    f32 time;
} Hit;

Vec2 vec2_add(Vec2 a, Vec2 b);
Vec2 vec2_sub(Vec2 a, Vec2 b);
Vec2 vec2_mult(Vec2 vector, f32 scalar);
Vec2 vec2_normalized(Vec2 vector);

//returns the intersection point of a ray and a segment. 
Hit vec2_ray_segment_intersection(Vec2 ray, Vec2 ray_start, Vec2 seg_start, Vec2 seg_end);

//Returns the angle of the vector in radians.
f32 vec2_get_angle(Vec2 vector);

void vec2_print(Vec2 vector);