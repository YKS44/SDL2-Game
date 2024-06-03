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
    RectEntity player = {.rect.h = 100, .rect.w = 100, .rect.pos.x = 300, .rect.pos.y = 500, .vel.x = 0, .vel.y = 0};

    Rect wall1 = {.h = 1000, .w = 5, .pos.x = screen_width-5, .pos.y = 0};
    Rect wall2 = {.h = 1000, .w = 5, .pos.x = 0, .pos.y = 0};
    SDL_Rect wr1 = {.x = wall1.pos.x, .y = wall1.pos.y, .h = wall1.h, .w = wall1.w};
    SDL_Rect wr2 = {.x = wall2.pos.x, .y = wall2.pos.y, .h = wall2.h, .w = wall2.w};

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
        SDL_SetRenderDrawColor(global.rendering.renderer, 0, 0, 0, 255);
        SDL_RenderClear(global.rendering.renderer);

        if(KEYS[SDLK_d].pressed){
            player.vel.x = 10;
        }
        if(KEYS[SDLK_d].released){
            player.vel.x = 0;
        }

        if(KEYS[SDLK_a].pressed){
            player.vel.x = -10;
        }
        if(KEYS[SDLK_a].released){
            player.vel.x = 0;
        }

        Hit one = entity_get_future_collision_point(player, wall1);
        Hit two = entity_get_future_collision_point(player, wall2);

        Hit theone;
        if(one.time > two.time){
            printf("right\n");
            theone = two;
        }else{
            printf("left\n");
            theone = one;
        }

        Vec2 vel = vec2_sub(theone.pos, player.rect.pos);

        player.rect.pos.x = theone.pos.x-player.rect.w/2;
        player.rect.pos.y = theone.pos.y+player.rect.h/2;
        
        SDL_Rect pr = {.x = player.rect.pos.x, .y = player.rect.pos.y, .w = player.rect.w, .h = player.rect.h};
        // printf("%f,%f\n",theone.pos.x,theone.pos.y);

        SDL_SetRenderDrawColor(global.rendering.renderer, 255,0,0,255);
        SDL_RenderFillRect(global.rendering.renderer, &wr1);
        SDL_RenderFillRect(global.rendering.renderer, &wr2);
        SDL_RenderFillRect(global.rendering.renderer, &pr);


        time_periodic();
        // entity_periodic();
        render_periodic();
        keyboard_update_instantKey();

        SDL_RenderPresent(global.rendering.renderer);

        f32 delay = (f32)TIME.loopDelay - (TIME.deltaTime*1000.0);
        if(delay > 0){ //only add a delay if delta time is less than the loop delay. This way, the delay is not called when the framerate is already lower than the target framerate.
            SDL_Delay(delay); //restrict the frame rate to 100fps 
        }
    }
    SDL_DestroyWindow(global.rendering.window);
    SDL_Quit();

    return (0);
}