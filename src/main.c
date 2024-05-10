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
    slime_init();
    entity_init();
    time_init();

    bool run = true;
    Point* lockPoint = (Point*)arraylist_get(player.points, 5); //TODO remove later. just for testing

    while(run){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    run = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    lockPoint->locked = true;
                    break;
                case SDL_MOUSEBUTTONUP:
                    lockPoint->locked = false;
                    break;
            }
        }
        SDL_GetMouseState(&global.mouseX, &global.mouseY);
        global.mouseY = -global.mouseY + screen_height;

        time_periodic();
        entity_periodic();
        render_periodic();
        slime_periodic();

        f32 delay = (f32)TIME.loopDelay - (TIME.deltaTime*1000.0);
        if(delay > 0){ //only add a delay if delta time is less than the loop delay. This way, the delay is not called when the framerate is already lower than the target framerate.
            SDL_Delay(delay); //restrict the frame rate to 100fps //TODO don't do the delay if the frame rate is already low because of calculations
        }
    }
    SDL_DestroyWindow(global.rendering.window);
    SDL_Quit();

    return (0);
}