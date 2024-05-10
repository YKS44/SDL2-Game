#pragma once

#include "rect.h"

typedef struct{
    Rect rect;
    Vec2 vel;
} RectEntity;

void rect_ent_update(RectEntity* ent);