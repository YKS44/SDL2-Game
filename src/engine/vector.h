#pragma once

#include "types.h"

typedef struct {
    f32 x;
    f32 y;
} Vec2;

Vec2 vec2_add(Vec2 a, Vec2 b);
Vec2 vec2_sub(Vec2 a, Vec2 b);
Vec2 vec2_mult(Vec2 vector, f32 scalar);
Vec2 vec2_normalized(Vec2 vector);

//Returns the angle of the vector in radians.
f32 vec2_get_angle(Vec2 vector);

void vec2_print(Vec2 vector);