#include "../keyboard.h"

Key KEYS[322];
ArrayList* instantKey;

void keyboard_init(){
    instantKey = arraylist_create(sizeof(u16));
}

void keyboard_update_justPressed(){
    for(int i = 0; i < instantKey->len; i++){
        u16 key = *((u16*)arraylist_get(instantKey, i));
        KEYS[key].pressed = false;
        KEYS[key].released = false;
    }
    instantKey = arraylist_clear(instantKey);
}