#include "../rect_ent.h"
#include "../timer.h"
#include "../global.h"
#include "../config.h"

void rect_ent_update(RectEntity* ent)
{
        ent->rect.pos.x += ent->vel.x * TIME.deltaTime;
        ent->rect.pos.y += ent->vel.y * TIME.deltaTime;
        if(ent->rect.pos.x <= 0 || ent->rect.pos.x >= screen_width){ //TODO remove later. made it just for fun
            ent->vel.x *= -1.0;

        }
        if(ent->rect.pos.y <= 0 || ent->rect.pos.y >= screen_height){
            ent->vel.y *= -1.0;
        }
}