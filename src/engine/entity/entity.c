#include "../entity.h"
#include "../global.h"
#include "../util.h"
#include "../config.h"
#include "../timer.h"
#include "../rect_ent.h"

ArrayList* entity_list = NULL;
void entity_init(){
    entity_list = arraylist_create(sizeof(Entity));
    for(int i = 0; i < 10; i++){
        Entity ent;
        ent.type = RectType;

        ent.RECT_ENT.rect.pos.x = random_range(0, screen_width);
        ent.RECT_ENT.rect.pos.y = random_range(0,screen_height);
        ent.RECT_ENT.rect.w = random_range(10,50);
        ent.RECT_ENT.rect.h = random_range(10,50);
        ent.RECT_ENT.vel.x = random_range(-100,100);
        ent.RECT_ENT.vel.y = random_range(-100,100);

        entity_add(ent);
    }
}

void entity_periodic(){
    for(int i = 0; i < entity_list->len; i++){
        Entity* ent = (Entity*) arraylist_get(entity_list, i);
        
        switch(ent->type){
            case RectType:
                rect_ent_update(&ent);
                break;

            case SlimeType:
                break;
        }
        ent->rect.pos.x += ent->vel.x * TIME.deltaTime;
        ent->rect.pos.y += ent->vel.y * TIME.deltaTime;
        if(ent->rect.pos.x <= 0 || ent->rect.pos.x >= screen_width){ //TODO remove later. made it just for fun
            ent->vel.x *= -1.0;

        }
        if(ent->rect.pos.y <= 0 || ent->rect.pos.y >= screen_height){
            ent->vel.y *= -1.0;
        }
    }
}

//adds the new entity to the list of entities to update and returns its pointer
Entity* entity_add(Entity ent){
    Entity* addedEntity = (Entity*) arraylist_append(entity_list, &ent);
    return addedEntity;
}

void entity_print_info(Entity ent){
    printf("X: %f\n", ent.rect.pos.x);
    printf("Y: %f\n", ent.rect.pos.y);
    printf("W: %u\n", ent.rect.w);
    printf("H: %u\n", ent.rect.h);
    printf("VX: %f\n", ent.vel.x);
    printf("VY: %f\n", ent.vel.y);
}