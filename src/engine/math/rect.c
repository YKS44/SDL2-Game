#include "../rect.h"
#include <math.h>
#include <stdio.h>

Rect rect_minkowski_diff(Rect rect1, Rect rect2){
    Rect diff;

    diff.pos.x = rect1.pos.x - rect2.pos.x;
    diff.pos.y = rect1.pos.y - rect2.pos.y;

    diff.h = (rect1.h+rect2.h);
    diff.w = (rect1.w+rect2.w);

    diff.pos.x -= rect2.w;
    diff.pos.y += rect2.h;
    
    return diff;
}

Vec2 rect_push_vec(Rect rect){
    Vec2 vec;
    f32 px = rect.pos.x;
    f32 py = rect.pos.y;

    if(fabsf(px) > fabsf(px + rect.w)){
        px += rect.w;
    }

    if(fabsf(py) > fabsf(py - rect.h)){
        py -= rect.h;
    }

    if(fabsf(px) > fabsf(py)){
        px = 0;
    }else{
        py = 0;
    }

    vec.x = px;
    vec.y = py;
    return vec;
}

bool rect_intersect_point(Rect rect, Point point){
    return point.point.x >= rect.pos.x &&
           point.point.x <= rect.pos.x+rect.w &&
           point.point.y >= rect.pos.y-rect.h &&
           point.point.y <= rect.pos.y;
}