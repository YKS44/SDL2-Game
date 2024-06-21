#include "../keyboard.h"

Key KEYS[322 + 3]; //+3 is the three mouse buttons. left, middle, right clicks
ArrayList* instantKey;
SDL_Keymod keymod;

void keyboard_init(){
    instantKey = arraylist_create(sizeof(u16));
    keymod = KMOD_NONE;
}

void keyboard_update_instantKey(){
    for(int i = 0; i < instantKey->len; i++){
        u16 key = *((u16*)arraylist_get(instantKey, i));
        KEYS[key].pressed = false;
        KEYS[key].released = false;
    }
    instantKey = arraylist_clear(instantKey);
}