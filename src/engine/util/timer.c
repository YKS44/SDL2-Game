#include "../timer.h"
#include "../global.h"
#include "../config.h"

const f32 MS_TO_SEC = 1.0/1000.0;

void time_init(){
    TIME.deltaTime = 0;
    TIME.now = 0;
    TIME.prev = 0;
    TIME.loopDelay = 1000 / frame_rate;
}

void time_periodic(){
    TIME.now = SDL_GetTicks64();

    if(TIME.now == TIME.prev){ //if the previous time and current time is the same because SDL2 is bad, then just skip calculating the deltatime for this frame.
        TIME.prev = TIME.now;
        return;
    }
    TIME.deltaTime = (f32)(TIME.now - TIME.prev) * MS_TO_SEC; //convert to seconds
    TIME.prev = TIME.now;
}