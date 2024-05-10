#pragma once

#include "rect.h"
#include "types.h"
#include "render.h"
#include "arraylist.h"
#include "vector.h"
#include "slime.h"
#include "rect_ent.h"

#define RECT_ENT u.rectEntity
#define SLIME_ENT u.slimeEntity

typedef enum {
    RectType,
    SlimeType
} EntityType;

typedef struct {
    EntityType type;

    union{
        RectEntity rectEntity;
        Slime slimeEntity;
    } u;
} Entity;

extern ArrayList* entity_list;

void entity_init();
void entity_periodic();
Entity* entity_add(Entity ent);
void entity_print_info(Entity ent);