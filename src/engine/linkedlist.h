#pragma once

#include "types.h"

typedef struct Node Node;

struct Node{
    Node* prev;
    void* item;
    Node* next;
};

typedef struct{
    u32 len;
    usize item_size;
    Node* head;
} LinkedList;


LinkedList* linkedlist_create(usize item_size);

//Adds an item to the linked list and returns the pointer to the node.
Node* linkedlist_append(LinkedList* list, void* item);
void linked_list_remove(LinkedList* list, Node* loc);