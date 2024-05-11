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

int main()
{
    render_init();
    entity_init();
    time_init();

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

    Entity diff;

    diff.type = RectType;
    diff.u.rectEntity.rect.h = 0;
    diff.u.rectEntity.rect.w = 0;
    diff.u.rectEntity.rect.pos.x = 0;
    diff.u.rectEntity.rect.pos.y = 0;
    diff.u.rectEntity.vel.x = 0;
    diff.u.rectEntity.vel.y = 0;

    entity_add(mouse);
    entity_add(rec);
    entity_add(diff);

    while(run){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    run = false;
                    break;
            }
        }
        SDL_GetMouseState(&global.mouseX, &global.mouseY);
        global.mouseY = -global.mouseY + screen_height;

        mouse.u.rectEntity.rect.pos.x = global.mouseX;
        mouse.u.rectEntity.rect.pos.y = global.mouseY;

        Rect min = rect_minkowski_diff(rec.u.rectEntity.rect, diff.u.rectEntity.rect);

        diff.u.rectEntity.rect.h = min.h;
        diff.u.rectEntity.rect.w = min.w;
        diff.u.rectEntity.rect.pos.x = min.pos.x;
        diff.u.rectEntity.rect.pos.y = min.pos.y;

        time_periodic();
        // entity_periodic();
        render_periodic();

        f32 delay = (f32)TIME.loopDelay - (TIME.deltaTime*1000.0);
        if(delay > 0){ //only add a delay if delta time is less than the loop delay. This way, the delay is not called when the framerate is already lower than the target framerate.
            SDL_Delay(delay); //restrict the frame rate to 100fps //TODO don't do the delay if the frame rate is already low because of calculations
        }
    }
    SDL_DestroyWindow(global.rendering.window);
    SDL_Quit();

    return (0);
}