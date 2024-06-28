#include "../slime.h"
#include <stdbool.h>
#include <math.h>
#include "../util.h"
#include "../vector.h"
#include "../render.h"
#include "../config.h"
#include "../global.h"
#include "../keyboard.h"

Slime slime_create(i32 pts[][2], usize numPts, u32 connections[][2], usize numCon, i32 scale, f32 elasticity){
    Slime slime;

    ArrayList* points = arraylist_create(sizeof(Point));
    ArrayList* lines = arraylist_create(sizeof(Line));

    for(int i = 0; i < numPts; i++){
        Point point;

        point.point.x = pts[i][0] * scale;
        point.point.y = pts[i][1] * scale+1000; //TODO remove +500

        point.prevPoint.x = point.point.x;
        point.prevPoint.y = point.point.y;
        
        arraylist_append(points, &point);
    }

    for(int i = 0; i < numCon; i++){
        Line line;
        line.idx1 = connections[i][0];
        line.idx2 = connections[i][1];

        Vec2 p1 = *((Vec2*)arraylist_get(points,line.idx1));
        Vec2 p2 = *((Vec2*)arraylist_get(points,line.idx2));

        f32 dist = hypot(p2.x-p1.x, p2.y-p1.y);
        line.length = dist;

        arraylist_append(lines, &line);
    }

    slime.lines = lines;
    slime.points = points;
    slime.elasticity = elasticity;

    return slime;
}

void slime_update(Slime* slime){

    for(int i = 0; i < slime->points->len; i++){
        Point* point = (Point*)arraylist_get(slime->points,i);
        
        if(i == 5 && KEYS[LEFT_MOUSE].held){
            point->point.x = global.mouseX;
            point->point.y = global.mouseY;
            point->prevPoint = point->point;
            continue;
        }
        Vec2 vel = vec2_sub(point->point,point->prevPoint);

        vel.y += -1;

        if(i == 0){
            printf("%f\n", vel.y);
            // printf("%f\n", TIME.deltaTime);

        }

        // if(point->point.y < 0){
        //     vel.y = -point->point.y;
        // }

        point->prevPoint = point->point;
        point->point = vec2_add(point->point, vel);
    }

    for(int i = 0; i < slime->lines->len; i++){
        if(i == 5 && KEYS[LEFT_MOUSE].held){
            continue;
        }

        Line line = *((Line*)arraylist_get(slime->lines,i));
        Point* p1 = (Point*)arraylist_get(slime->points, line.idx1);
        Point* p2 = (Point*)arraylist_get(slime->points, line.idx2);

        Vec2 dir = vec2_normalized(vec2_sub(p1->point,p2->point));

        f32 dist = hypot(p2->point.x-p1->point.x, p2->point.y-p1->point.y);

        Vec2 vel = vec2_mult(dir, (line.length-dist)/2 * slime->elasticity);
        vel = vec2_mult(vel, TIME.deltaTime);
        
        p1->point = vec2_add(p1->point,vel);
        p2->point = vec2_sub(p2->point, vel);
    }
}

void slime_render(Slime slime){
    for(int i = 0; i < slime.lines->len; i++){
        Line line = *((Line*)arraylist_get(slime.lines,i));
        Point p1 = *((Point*)arraylist_get(slime.points, line.idx1));
        Point p2 = *((Point*)arraylist_get(slime.points, line.idx2));

        SDL_SetRenderDrawColor(global.rendering.renderer, 255,255,255,255);
        SDL_RenderDrawLine(global.rendering.renderer, p1.point.x, -p1.point.y+screen_height, p2.point.x, -p2.point.y+screen_height);
    }
}

void slime_destroy(Slime* slime){
    //TODO implement later
}