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

u32 loop_delay = 0;

int main()
{
    loop_delay = 1000 / frame_rate; //1000ms / set framerate

    render_init();
    entity_init();

    bool run = true;
    while(run){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    run = false;
                    break;
            }
        }
        entity_periodic();
        render_periodic();

        SDL_Delay(loop_delay); //restrict the frame rate to 100fps
    }
    SDL_DestroyWindow(global.rendering.window);
    SDL_Quit();

    return (0);
}