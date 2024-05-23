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
                    if(!KEYS[event.key.keysym.sym].held){
                        KEYS[event.key.keysym.sym].pressed = true;
                    }
                    KEYS[event.key.keysym.sym].held = true;
                    arraylist_append(instantKey, &event.key.keysym.sym);
                    break;
                case SDL_KEYUP:
                    KEYS[event.key.keysym.sym].held = false;
                    KEYS[event.key.keysym.sym].released = true;
                    arraylist_append(instantKey, &event.key.keysym.sym);
                    break;
            }
        }

        SDL_SetRenderDrawColor(global.rendering.renderer, 0, 0, 0, 255);
        SDL_RenderClear(global.rendering.renderer);
        render_rect(rec.u.rectEntity.rect,255);

        if(KEYS[SDLK_a].pressed){
            printf("pressed\n");
        }
        if(KEYS[SDLK_a].held){
            printf("held\n");
        }
        if(KEYS[SDLK_a].released){
            printf("released\n");
        }

        if(mouseHeld){
            Rect added = rect_size_sum(rec.u.rectEntity.rect, add.u.rectEntity.rect);

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
        // mouse.u.rectEntity.rect.pos.x = global.mouseX;
        // mouse.u.rectEntity.rect.pos.y = global.mouseY;

        // Rect min = rect_minkowski_diff(rec.u.rectEntity.rect, mouse.u.rectEntity.rect);


        u32 r = 255;

        Point p;
        p.point.x = 0;
        p.point.y = 0;
        // if(rect_intersect_point(min, p)){
        //     // r = 100;
        //     Vec2 push_vec = rect_push_vec(min);
        //     mouse.u.rectEntity.rect.pos = vec2_add(mouse.u.rectEntity.rect.pos, push_vec);
        // }

        // render_rect(mouse.u.rectEntity.rect,r);
        // render_rect(min,255);

        SDL_RenderPresent(global.rendering.renderer);

        time_periodic();
        // entity_periodic();
        // render_periodic();
        keyboard_update_justPressed();

        f32 delay = (f32)TIME.loopDelay - (TIME.deltaTime*1000.0);
        if(delay > 0){ //only add a delay if delta time is less than the loop delay. This way, the delay is not called when the framerate is already lower than the target framerate.
            SDL_Delay(delay); //restrict the frame rate to 100fps //TODO don't do the delay if the frame rate is already low because of calculations
        }
    }
    SDL_DestroyWindow(global.rendering.window);
    SDL_Quit();

    return (0);
}