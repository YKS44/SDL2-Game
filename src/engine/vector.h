#pragma once

#include "types.h"

typedef struct {
    i32 x;
    i32 y;
} Vec2;

Vec2 add(Vec2 a, Vec2 b);
Vec2 sub(Vec2 a, Vec2 b);
Vec2 mult(f32 scalar, Vec2 vector);

//Returns the angle of the vector in radians.
f32 get_angle(Vec2 vector);