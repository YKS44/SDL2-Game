#include "../entity.h"
#include "../global.h"
#include "../util.h"
#include "../config.h"
#include "../timer.h"
#include "../rect_ent.h"

LinkedList* entity_list = NULL;
void entity_init(){
    entity_list = linkedlist_create(sizeof(Entity));

    // i32 points[6][2] = {{0,0},{2,0},{0,-2},{2,-2},{1,-3},{1,1}};
    // u32 connections[10][2] = {{0,1},{0,2},{0,5},{1,3},{1,5},{2,3},{2,4},{3,4} ,{0,3},{1,2}};

    // Slime slime = slime_create(points, sizeof(points)/sizeof(points[0]), connections, sizeof(connections)/sizeof(connections[0]), 50, 0.5);
    // Entity sl;
    // sl.type = SlimeType;
    // sl.u.slimeEntity = slime;
    // entity_add(sl);
}

void entity_periodic(){
    Node* cur = entity_list->head;
    for(int i = 0; i < entity_list->len; i++){
        Entity* ent = (Entity*) cur->item;
        
        switch(ent->type){
            case RectType:
                rect_ent_update(&(ent->u.rectEntity));
                break;

            case SlimeType:
                slime_update(&(ent->u.slimeEntity));
                break;
        }
        cur = cur->prev;
    }
}

Node* entity_add(Entity* ent){
    Node* addedEntity = linkedlist_append(entity_list, ent);
    return addedEntity;
}

Hit entity_get_future_collision_point(RectEntity ent, Rect rect){
    Rect size_sum = rect_size_sum(rect, ent.rect);
    Vec2 midpt = rect_get_midpoint(ent.rect);
    Hit hit_point = rect_intersect_ray(size_sum, midpt, ent.vel);
    if(!hit_point.is_hit){
        hit_point.pos = vec2_add(midpt,ent.vel);
    }else{
        printf("hit!\n");
    }
    return hit_point;
}

void entity_print_info(Entity ent){
    // printf("X: %f\n", ent.rect.pos.x);
    // printf("Y: %f\n", ent.rect.pos.y);
    // printf("W: %u\n", ent.rect.w);
    // printf("H: %u\n", ent.rect.h);
    // printf("VX: %f\n", ent.vel.x);
    // printf("VY: %f\n", ent.vel.y);
}