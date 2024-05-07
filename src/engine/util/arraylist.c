#include <stdlib.h>
#include <string.h>
#include "../types.h"
#include "../arraylist.h"
#include "../util.h"

//make a new arraylist and return its pointer
ArrayList* arraylist_create(usize item_size){
    ArrayList* list = malloc(sizeof(ArrayList));

    if(!list){
        ERROR_RETURN(NULL, "Could not allocate enough memory for ArrayList.\n");
    }
    
    list->item_size = item_size;
    list->len = 0;
    list->items = malloc(0);

    return list;
}

//attempts to add an item to the list and returns its pointer
void* arraylist_append(ArrayList* list, void* item){
    usize curretListByteSize = list->len * list->item_size;

    list->items = realloc(list->items, curretListByteSize + list->item_size);

    if(!list){
        ERROR_RETURN(NULL, "Could not allocate enough memory for ArrayList.\n");
    }
    void* appendedPtr = list->items + list->item_size * list->len;
    list->len++;

    memcpy(appendedPtr, item, list->item_size);

    return appendedPtr;
}

void* arraylist_get(ArrayList* list, u32 index){
    if(index < 0 || index >= list->len){
        ERROR_RETURN(NULL, "Array index out of bounds.");
    }

    void* requestedIndexPtr = list->items + list->item_size * index;
    if(!requestedIndexPtr){
        ERROR_RETURN(NULL, "could not get array pointer");
    }
    return requestedIndexPtr;
}

void arraylist_remove(ArrayList* list, u32 index){
    if(index < 0 || index >= list->len){
        ERROR_EXIT("ArrayList index out of bounds.");
    }

    void* lastItem = list->items + list->item_size * (list->len-1);
    void* removeLoc = list->items;

    // list->len--;
    memcpy(removeLoc, lastItem, list->item_size);
}
