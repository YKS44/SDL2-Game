#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#include "engine/global.h"
#include "engine/render.h"
#include "engine/entity.h"

#include "engine/arraylist.h"
#include "engine/types.h"
#include "engine/util.h"
#include "engine/config.h"
#include "engine/slime.h"
#include "engine/timer.h"
#include "engine/keyboard.h"

int main()
{
    render_init();
    entity_init();
    time_init();
    keyboard_init();

    bool run = true;

    while(run){
        SDL_GetMouseState(&global.mouseX, &global.mouseY);
        global.mouseY = -global.mouseY + screen_height;

        SDL_Event event;
        SDL_Keycode keycode;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    run = false;
                    break;
                case SDL_KEYDOWN:
                    keycode = event.key.keysym.sym;

                    if(keycode < 322){ //for some reason keysym.sym also detects modifer keys, but their numbers are really big, so only update when you know its not a mod key.
                        if(!KEYS[keycode].held){ //cuz if you keep holding down your keyboard, mac book detects it as pressing it multiple times
                            KEYS[keycode].pressed = true;
                        }
                        KEYS[keycode].held = true;
                        arraylist_append(instantKey, &keycode);
                    }else{//only pressed some modifer key
                        keymod = event.key.keysym.mod; 
                    }           
                    break;
                case SDL_KEYUP:
                    keycode = event.key.keysym.sym;
                    
                    if(keycode < 322){
                        KEYS[keycode].held = false;
                        KEYS[keycode].released = true;
                        arraylist_append(instantKey, &keycode);
                    }else{
                        keymod = KMOD_NONE;
                    }
                    break;
            }
        }

        time_periodic();
        // entity_periodic();
        // render_periodic();
        keyboard_update_instantKey();

        f32 delay = (f32)TIME.loopDelay - (TIME.deltaTime*1000.0);
        if(delay > 0){ //only add a delay if delta time is less than the loop delay. This way, the delay is not called when the framerate is already lower than the target framerate.
            SDL_Delay(delay); //restrict the frame rate to 100fps //TODO don't do the delay if the frame rate is already low because of calculations
        }
    }
    SDL_DestroyWindow(global.rendering.window);
    SDL_Quit();

    return (0);
}