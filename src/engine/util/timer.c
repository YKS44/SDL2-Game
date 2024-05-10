#include "../timer.h"
#include "../global.h"
#include "../config.h"

void time_init(){
    TIME.deltaTime = 0;
    TIME.now = 0;
    TIME.prev = 0;
    TIME.loopDelay = 1000 / frame_rate;
}

void time_periodic(){
    TIME.now = SDL_GetTicks64();
    TIME.deltaTime = (f32)(TIME.now - TIME.prev) / 1000.0; //convert to seconds
    TIME.prev = TIME.now;
}