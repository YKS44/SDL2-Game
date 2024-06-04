#include "../render.h"
#include "../global.h"
#include "../types.h"
#include "../config.h"
#include "../arraylist.h"
#include "../entity.h"

static void render_set_draw_color(RGBA color){
    SDL_SetRenderDrawColor(global.rendering.renderer, color.r, color.g, color.b, color.a);
}

void render_init(void){
    global.rendering.window = SDL_CreateWindow(screen_title, screen_pos_x, screen_pos_y, screen_width, screen_height, SDL_WINDOW_SHOWN);
    global.rendering.renderer = SDL_CreateRenderer(global.rendering.window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Init(SDL_INIT_EVERYTHING);
} 

void render_periodic(void){
    //clear the screen with black
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
}

void render_fill_rect(Rect rect, RGBA color){
    SDL_Rect r;
    r.x = rect.pos.x;
    r.y = rect.pos.y;
    r.w = rect.w;
    r.h = rect.h;

    r.y = -r.y + screen_height;

    render_set_draw_color(color);
    SDL_RenderFillRect(global.rendering.renderer, &r);
}

void render_line(Vec2 p1, Vec2 p2, RGBA color){
    p1.y = -p1.y + screen_height;
    p2.y = -p2.y + screen_height;

    render_set_draw_color(color);
    SDL_RenderDrawLine(global.rendering.renderer, p1.x, p1.y, p2.x, p2.y);
}


