#pragma once

#include "rect.h"
#include "types.h"
#include "render.h"
#include "arraylist.h"
#include "vector.h"
#include "slime.h"
#include "rect_ent.h"
#include "linkedlist.h"

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

extern LinkedList* entity_list;

void entity_init();
void entity_periodic();

//adds the new entity to the list of entities to update and returns the pointer to the node in the linked list. 
Node* entity_add(Entity* ent);
void entity_print_info(Entity ent);
//returns the future collision point between a RectEntity and a rect, if it exists. Otherwise, it just returns where the rect ent would be with the given velocity. 
Hit entity_get_future_collision_point(RectEntity ent, Rect rect);