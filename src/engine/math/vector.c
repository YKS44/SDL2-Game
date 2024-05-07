#include "../vector.h"
#include <math.h>

Vec2 add(Vec2 a, Vec2 b){
    Vec2 added;
    added.x = a.x + b.x;
    added.y = a.y + b.y;

    return added;
}

Vec2 sub(Vec2 a, Vec2 b){
    Vec2 subtracted;
    subtracted.x = a.x - b.x;
    subtracted.y = a.y - b.y;

    return subtracted;
}

Vec2 mult(f32 scalar, Vec2 vector){
    Vec2 multiplied;

    multiplied.x *= scalar;
    multiplied.y *= scalar;

    return multiplied;
}

f32 get_angle(Vec2 vector){
    f32 angle = atan2(vector.y, vector.x);

    return angle;
}