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

    Entity mouse;
    mouse.type = RectType;
    mouse.u.rectEntity.rect.w = 50;
    mouse.u.rectEntity.rect.h = 50;
    mouse.u.rectEntity.rect.pos.x = 0;
    mouse.u.rectEntity.rect.pos.y = 0;
    mouse.u.rectEntity.vel.x = 0;
    mouse.u.rectEntity.vel.y = 0;

    Entity rec;
    rec.type = RectType;
    rec.u.rectEntity.rect.h = 100;
    rec.u.rectEntity.rect.w = 100;
    rec.u.rectEntity.rect.pos.x = 500;
    rec.u.rectEntity.rect.pos.y = 500;
    rec.u.rectEntity.vel.x = 0;
    rec.u.rectEntity.vel.y = 0;

    Entity add;
    add.type = RectType;
    add.u.rectEntity.rect.h = 100;
    add.u.rectEntity.rect.w = 100;
    add.u.rectEntity.rect.pos.x = 500;
    add.u.rectEntity.rect.pos.y = 500;
    add.u.rectEntity.vel.x = 0;
    add.u.rectEntity.vel.y = 0;

    Vec2 mouseStart = {.x = 0, .y = 0};
    Vec2 mouseCur = {.x = 0, .y = 0};
    bool mouseHeld = false;

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
                case SDL_MOUSEBUTTONDOWN:
                    mouseHeld = true;
                    mouseStart = (Vec2){.x = global.mouseX, .y = global.mouseY};
                    break;
                case SDL_MOUSEBUTTONUP:
                    mouseHeld = false;
                    break;
                case SDL_KEYDOWN:
                    keycode = event.key.keysym.sym;

                    if(keycode < 322){
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
        render_rect(rec.u.rectEntity.rect,255);

        if(mouseHeld){
            mouseCur = (Vec2) {.x = global.mouseX, .y = global.mouseY};
            Vec2 ray = vec2_sub(mouseCur, mouseStart);
            Hit hit = rect_intersect_ray(rec.u.rectEntity.rect, mouseStart, ray);
            SDL_RenderDrawLine(global.rendering.renderer, mouseStart.x, -mouseStart.y + screen_height, mouseCur.x, -mouseCur.y + screen_height);
            if(hit.is_hit){
                SDL_Rect hitPoint;
                hitPoint.h = 10;
                hitPoint.w = 10;
                hitPoint.x = hit.pos.x;
                hitPoint.y = hit.pos.y;
                hitPoint.y = -hitPoint.y + screen_height;

                SDL_SetRenderDrawColor(global.rendering.renderer, 255, 255, 255, 255);

                SDL_RenderFillRect(global.rendering.renderer, &hitPoint);

            }
        }

        SDL_RenderPresent(global.rendering.renderer);

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