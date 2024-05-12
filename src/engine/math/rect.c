#include "../rect.h"

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

Vec2 rect_penetration_vec(Rect rect){
    Vec2 vec;
    f32 px = -rect.pos.x;
    f32 py = 
}

bool rect_intersect_point(Rect rect, Point point){
    return point.point.x >= rect.pos.x &&
           point.point.x <= rect.pos.x+rect.w &&
           point.point.y >= rect.pos.y-rect.h &&
           point.point.y <= rect.pos.y;
}