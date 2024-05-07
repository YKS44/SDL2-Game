#pragma once

#include "rect.h"
#include "types.h"
#include "render.h"
#include "arraylist.h"
#include "vector.h"

typedef struct {
    Rect rect;
    Vec2 vel;
    RenderData render_data;
} Entity;

extern ArrayList* entity_list;

void entity_init();
void entity_periodic();
Entity* entity_add(Entity ent);
void entity_print_info(Entity ent);