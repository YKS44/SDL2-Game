#include "../rect.h"
#include <math.h>
#include <stdio.h>
#include "../util.h"
#include <SDL2/SDL.h>
#include "../global.h"
#include "../config.h"

Rect rect_minkowski_diff(Rect rect1, Rect rect2){
    Rect diff;

    diff.pos.x = rect1.pos.x - rect2.pos.x;
    diff.pos.y = rect1.pos.y - rect2.pos.y;

    diff.h = (rect1.h+rect2.h);
    diff.w = (rect1.w+rect2.w);

    diff.pos.x -= rect2.w;
    diff.pos.y += rect2.h;
    
    return diff;
}

Vec2 rect_push_vec(Rect rect){
    Vec2 vec;
    f32 px = rect.pos.x;
    f32 py = rect.pos.y;

    if(fabsf(px) > fabsf(px + rect.w)){
        px += rect.w;
    }

    if(fabsf(py) > fabsf(py - rect.h)){
        py -= rect.h;
    }

    if(fabsf(px) > fabsf(py)){
        px = 0;
    }else{
        py = 0;
    }
    vec.x = px;
    vec.y = py;
    return vec;
}

Hit rect_intersect_ray(Rect rect, Vec2 ray_start, Vec2 ray){
    Hit hit;
    f32 nearX, farX, nearY, farY, nearXT, farXT, nearYT, farYT;
    // ray_start.x += sign(ray.x) * SMOL; //if the x or y of the start of the ray is directly in the center for some reason, it will shift its direction slightly to where the ray is pointing.
    // ray_start.y += sign(ray.y) * SMOL; //maybe this is too unlikely, but who knows

    if(ray.x > 0){
        nearX = rect.pos.x;
        farX = rect.pos.x + rect.w;
    }else{
        nearX = rect.pos.x + rect.w;
        farX = rect.pos.x;
    }

    if(ray.y > 0){
        nearY = rect.pos.y - rect.h;
        farY = rect.pos.y;
    }else{
        nearY = rect.pos.y;
        farY = rect.pos.y - rect.h;
    }

    if(ray.x != 0.0){
        nearXT = (nearX - ray_start.x) / ray.x;
        farXT = (farX - ray_start.x) / ray.x;
    }else{
        nearXT = INFINITY;
        farXT = INFINITY;
    }

    if(ray.y != 0.0){
        nearYT = (nearY - ray_start.y) / ray.y;
        farYT = (farY - ray_start.y) / ray.y;
    }else{
        nearYT = INFINITY;
        farYT = INFINITY;
    }
    SDL_SetRenderDrawColor(global.rendering.renderer, 255,255,255,255);
    SDL_RenderDrawLine(global.rendering.renderer, ray.x*nearXT+ray_start.x, 500, ray.x*nearXT+ray_start.x, -500);
    SDL_RenderDrawLine(global.rendering.renderer, 1000, -(ray.y*nearYT+ray_start.y)+screen_height, -500, -(ray.y*nearYT+ray_start.y)+screen_height);

    SDL_SetRenderDrawColor(global.rendering.renderer, 255,0,255,255);
    SDL_RenderDrawLine(global.rendering.renderer, ray.x*farXT+ray_start.x, 500, ray.x*farXT+ray_start.x, -500);
    SDL_RenderDrawLine(global.rendering.renderer, 1000, -(ray.y*farYT+ray_start.y)+screen_height, -500, -(ray.y*farYT+ray_start.y)+screen_height);


    if(fabsf(farXT) < nearYT || fabsf(farYT) < nearXT){
        hit.is_hit = false;
        printf("%f,%f,%f,%f\n",nearXT,fabsf(farXT),nearYT,fabsf(farYT));
        return hit;
    }

    f32 nearTime = nearXT > nearYT ? nearXT : nearYT; //get the bigger of the near times
    f32 farTime = farXT < farYT ? farXT : farYT; //get the smaller of the two far times

    if(nearTime > 1 || farTime < 0){
        hit.is_hit = false;
        printf("two\n");
        return hit;
    }

    f32 x = ray.x * nearTime + ray_start.x;
    f32 y = ray.y * nearTime + ray_start.y;
    hit.is_hit = true;
    hit.pos = (Vec2) {.x = x, .y = y};
    hit.time = nearTime;
    return hit;
}


bool rect_intersect_point(Rect rect, Point point){
    return point.point.x >= rect.pos.x &&
           point.point.x <= rect.pos.x+rect.w &&
           point.point.y >= rect.pos.y-rect.h &&
           point.point.y <= rect.pos.y;
}