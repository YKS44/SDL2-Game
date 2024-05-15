#include "../vector.h"
#include <math.h>
#include <stdio.h>
#include "../util.h"

Vec2 vec2_add(Vec2 a, Vec2 b){
    Vec2 added;
    added.x = a.x + b.x;
    added.y = a.y + b.y;

    return added;
}

Vec2 vec2_sub(Vec2 a, Vec2 b){
    Vec2 subtracted;
    subtracted.x = a.x - b.x;
    subtracted.y = a.y - b.y;

    return subtracted;
}

Vec2 vec2_mult(Vec2 vector, f32 scalar){
    vector.x *= scalar;
    vector.y *= scalar;
    return vector;
}

Vec2 vec2_normalized(Vec2 vector){
    f32 magnitude = hypot(vector.x, vector.y);
    vector = vec2_mult(vector,1/magnitude);
    
    return vector;
}

Hit vec2_ray_segment_intersection(Vec2 ray, Vec2 ray_start, Vec2 seg_start, Vec2 seg_end){
    Hit hit;
    return hit;
}


void vec2_print(Vec2 vector){
    printf("<%f,%f>\n",vector.x,vector.y);
}

f32 vec2_get_angle(Vec2 vector){
    f32 angle = atan2(vector.y, vector.x);

    return angle;
}