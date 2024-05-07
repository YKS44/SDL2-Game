#pragma once

#include "../../vector.h"

typedef struct{
    Vec2 point;
    Vec2 prevPoint;
    bool locked;
} Point;