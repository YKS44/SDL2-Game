#pragma once

#include "rect.h"

typedef struct{
    Rect rect;
    Vec2 vel;
} RectEntity;

void rect_ent_update(RectEntity* ent);
void rect_ent_render(RectEntity ent);
RectEntity rect_ent_create(Rect rect);