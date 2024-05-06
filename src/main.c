#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#include "engine/global.h"
#include "engine/render.h"

#include "engine/arraylist.h"
#include "engine/types.h"

int main()
{
    render_init();
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

        render_periodic();
    }
    
    return (0);
}