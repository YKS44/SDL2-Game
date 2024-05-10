#include "../slime.h"
#include <stdbool.h>
#include <math.h>
#include "../util.h"
#include "../vector.h"
#include "../render.h"
#include "../config.h"
#include "../global.h"

Slime player = {0};
const f32 elasticity = 1.0;

void slime_init(){
    i32 scale = 50;
    i32 pts[6][2] = {{0,0},{2,0},{0,-2},{2,-2},{1,-3},{1,1}};
    u32 connections[10][2] = {{0,1},{0,2},{0,5},{1,3},{1,5},{2,3},{2,4},{3,4} ,{0,3},{1,2}};
    // i32 pts [2][2] = {{0,0}, {0,-1}};
    // u32 connections[1][2] = {{0,1}};

    ArrayList* points = arraylist_create(sizeof(Point));
    ArrayList* lines = arraylist_create(sizeof(Line));

    for(int i = 0; i < sizeof(pts)/sizeof(pts[0]); i++){
        Point point;

        point.point.x = pts[i][0] * scale;
        point.point.y = pts[i][1] * scale+500;

        point.prevPoint.x = point.point.x;
        point.prevPoint.y = point.point.y;

        if(i == 5){
            point.locked = true;
        }else{
            point.locked = false;
        }
        
        arraylist_append(points, &point);
    }

    for(int i = 0; i < sizeof(connections)/sizeof(connections[0]); i++){
        Line line;
        line.idx1 = connections[i][0];
        line.idx2 = connections[i][1];

        Vec2 p1 = *((Vec2*)arraylist_get(points,line.idx1));
        Vec2 p2 = *((Vec2*)arraylist_get(points,line.idx2));

        f32 dist = hypot(p2.x-p1.x, p2.y-p1.y);
        line.length = dist;

        arraylist_append(lines, &line);
    }

    player.lines = lines;
    player.points = points;

}

void slime_periodic(){
    for(int i = 0; i < player.points->len; i++){
        Point* point = (Point*)arraylist_get(player.points,i);

        if(point->locked) {
            point->point.x = global.mouseX;
            point->point.y = global.mouseY;
            point->prevPoint = point->point;
            continue;
        }

        
        Vec2 vel = vec2_sub(point->point,point->prevPoint);

        vel.y += gravity;

        point->prevPoint = point->point;

        // printf("before\n");
        // vec2_print(point->point);
        // point->point.y = a;

        // printf("after\n");
        // vec2_print(point->point);
        // printf("\n");
        // point->point = vec2_add(point->point,vel);

        if(point->point.y < 0){
            point->point.y = 0;
            point->prevPoint = point->point;
        }
    }

    for(int i = 0; i < player.lines->len; i++){
        Line line = *((Line*)arraylist_get(player.lines,i));
        Point* p1 = (Point*)arraylist_get(player.points, line.idx1);
        Point* p2 = (Point*)arraylist_get(player.points, line.idx2);

        Vec2 dir = vec2_normalized(vec2_sub(p1->point,p2->point));

        f32 dist = hypot(p2->point.x-p1->point.x, p2->point.y-p1->point.y);

        Vec2 vel = vec2_mult(dir, (line.length-dist)/2 * elasticity);
        
        if(!p1->locked){
            p1->point = vec2_add(p1->point,vel);
        }
        if(!p2->locked){
            p2->point = vec2_sub(p2->point, vel);
        }
    }

    SDL_SetRenderDrawColor(global.rendering.renderer, 0, 0, 0, 255);
    SDL_RenderClear(global.rendering.renderer);
    for(int i = 0; i < player.lines->len; i++){
        Line line = *((Line*)arraylist_get(player.lines,i));
        Point p1 = *((Point*)arraylist_get(player.points, line.idx1));
        Point p2 = *((Point*)arraylist_get(player.points, line.idx2));

        // vec2_print(p1.point);
        // vec2_print(p2.point);
        SDL_SetRenderDrawColor(global.rendering.renderer, 255,255,255,255);
        SDL_RenderDrawLine(global.rendering.renderer, p1.point.x, -p1.point.y+screen_height, p2.point.x, -p2.point.y+screen_height);
    }
    SDL_RenderPresent(global.rendering.renderer);

}