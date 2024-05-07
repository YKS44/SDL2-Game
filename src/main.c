#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#include "engine/global.h"
#include "engine/render.h"
#include "engine/entity.h"

#include "engine/arraylist.h"
#include "engine/types.h"
#include "engine/util.h"

int main()
{
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

        SDL_Delay(10); //restrict the frame rate to 100fps
    }
    
    return (0);
}