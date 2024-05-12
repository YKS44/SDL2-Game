#include "../render.h"
#include "../global.h"
#include "../types.h"
#include "../config.h"
#include "../arraylist.h"
#include "../entity.h"

void render_init(void){
    global.rendering.window = SDL_CreateWindow(screen_title, screen_pos_x, screen_pos_y, screen_width, screen_height, SDL_WINDOW_SHOWN);
    global.rendering.renderer = SDL_CreateRenderer(global.rendering.window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Init(SDL_INIT_EVERYTHING);

    global.rendering.render_entity_list = arraylist_create(sizeof(Entity));
    // global.rendering.tile_list = arraylist_create(sizeof(RenderData));
} 

void render_periodic(void){
    //clear the screen with black
    SDL_SetRenderDrawColor(global.rendering.renderer, 0, 0, 0, 255);
    SDL_RenderClear(global.rendering.renderer);

    //Draw the tiles first
    // for(int i = 0; i < global.rendering.tile_list->len; i++){
    //     RenderData render_data = *((RenderData*) arraylist_get(global.rendering.tile_list, i));
    //     SDL_Rect rect;
    //     rect.x = render_data.rect.pos.x;
    //     rect.y = render_data.rect.pos.y;
    //     rect.w = render_data.rect.w;
    //     rect.h = render_data.rect.h;

    //     rect.y = -rect.y + screen_height; //since the origin of the screen coordinate system is in the top left, I flip signs for the y and subtract by the height of the screen to make bottom left the origin.

    //     SDL_SetRenderDrawColor(global.rendering.renderer, render_data.rgba[0], render_data.rgba[1], render_data.rgba[2], render_data.rgba[3]);
    //     SDL_RenderFillRect(global.rendering.renderer, &rect);
    // }

    // //Then draw the entities on top of it
    for(int i = 0; i < entity_list->len; i++){
        Entity entity = *((Entity*) arraylist_get(entity_list, i));
        
        switch(entity.type){
            case RectType:
                rect_ent_render(entity.u.rectEntity);
                break;

            case SlimeType:
                slime_render(entity.u.slimeEntity);
                break;
        }
    }

    //actually update the screen
    SDL_RenderPresent(global.rendering.renderer);
}

void render_rect(Rect rect, u32 ra){
    SDL_Rect r;
    r.x = rect.pos.x;
    r.y = rect.pos.y;
    r.w = rect.w;
    r.h = rect.h;

    r.y = -r.y + screen_height;

    SDL_SetRenderDrawColor(global.rendering.renderer, ra, 0, 0, 255);
    SDL_RenderFillRect(global.rendering.renderer, &r);
}

