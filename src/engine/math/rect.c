#include "../rect.h"

Rect rect_minkowski_diff(Rect rect1, Rect rect2){
    Rect diff;

    diff.pos.x = rect1.pos.x - rect2.pos.x;
    diff.pos.y = rect2.pos.y - rect2.pos.y;

    diff.h = (rect1.h+rect2.h)/2;
    diff.w = (rect1.w+rect2.w)/2;
    
    return diff;
}