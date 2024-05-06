#pragma once

#include "types.h"

typedef struct{
    void* items;
    u32 len;
    usize item_size;
} ArrayList;

ArrayList* arraylist_create(usize item_size);
u32 arraylist_append(ArrayList* list, void* item);
void* arraylist_get(ArrayList* list, u32 index);
void arraylist_remove(ArrayList* list, u32 index);