#include "../linkedlist.h"
#include "../util.h"
#include <stdlib.h>
#include <string.h>

LinkedList* linkedlist_create(usize item_size){
    LinkedList* list = malloc(sizeof(LinkedList));

    if(!list){
        ERROR_RETURN(NULL, "Could not allocate enough memory for LinkedList.\n");
    }

    list->item_size = item_size;
    list->len = 0;
    list->head = &((Node) {.prev = NULL, .item = NULL, .next = NULL});

    return list;
}

Node* linkedlist_append(LinkedList* list, void* item){
    Node* newHead = malloc(sizeof(Node));
    void* newItem = malloc(sizeof(list->item_size));

    if(!newHead){
        ERROR_RETURN(NULL, "Could not allocate enough memory for the new item for LinkedList.");
    }

    if(!newItem){
        ERROR_RETURN(NULL, "Could not allocate enough memory for the new item for LinkedList.");
    }

    memcpy(newItem, item, list->item_size);
    newHead->item = newItem;

    newHead->prev = list->head;
    list->head->next = newHead;

    list->head = newHead;
    list->len++;

    return newHead;
}

void linkedlist_remove(LinkedList* list, Node* loc){
    if(loc->prev){ //if the previous node is not null
        loc->prev->next = loc->next ? loc->next : NULL;
    }

    if(loc->next){
        loc->next->prev = loc->prev ? loc->prev : NULL;
    }

    list->len--;

    free(loc);
}