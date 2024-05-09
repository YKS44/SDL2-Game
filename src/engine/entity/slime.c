#include "../slime.h"
#include <stdbool.h>
#include <math.h>
#include "../util.h"
#include "../vector.h"
#include "../render.h"
#include "../config.h"

Slime player = {0};
f32 elasticity = 1.0;

void slime_init(){
    u32 scale = 10;
    i32 pts[6][2] = {{0,0},{2,0},{0,-2},{2,-2},{1,-3},{1,1}};
    u32 connections[6][2] = {{0,1},{0,2},{0,5},{1,3},{1,5},{2,3},{2,4},{3,4}};

    ArrayList* points = arraylist_create(sizeof(Point));
    ArrayList* lines = arraylist_create(sizeof(Line));

    for(int i = 0; i < sizeof(pts)/sizeof(pts[0]); i++){
        Point point;
        point.point.x = pts[i][0] * scale;
        point.point.y = pts[i][1] * scale;
        
        point.prevPoint.x = point.point.x;
        point.prevPoint.y = point.point.y;

        if(i == 5){
            point.locked = true;
        }else{
            point.locked = false;
        }
        arraylist_append(points, pts[i]);
    }

    for(int i = 0; i < sizeof(connections)/sizeof(connections[0]); i++){
        Line line;
        line.idx1 = connections[i][0];
        line.idx2 = connections[i][1];

        Vec2 p1 = *((Vec2*)arraylist_get(points, line.idx1));
        Vec2 p2 = *((Vec2*)arraylist_get(points,line.idx2));

        u32 dist = (u32) hypot(p2.x-p1.x, p2.y-p1.y);
        line.length = dist;
    }

    player.lines = lines;
    player.points = points;
}

void slime_periodic(){
    for(int i = 0; i < player.points->len; i++){
        Point point = *((Point*)arraylist_get(player.points,i));

        if(point.locked) continue;

        Vec2 vel = vec2_sub(point.point,point.prevPoint);
        vel.y += gravity;
        point.prevPoint = point.point;
        point.point = vec2_add(point.point,vel);
    }

    for(int i = 0; i < player.lines->len; i++){
        Line line = *((Line*)arraylist_get(player.lines,i));
        Point* p1 = (Point*)arraylist_get(player.points, line.idx1);
        Point* p2 = (Point*)arraylist_get(player.points, line.idx2);

        Vec2 midPt = vec2_add(p1->point,p2->point);
        midPt = vec2_mult(midPt, 0.5);

        Vec2 dir = vec2_normalized(vec2_sub(p1->point,midPt));

        u32 dist = (u32) hypot(p2->point.x-p1->point.x, p2->point.y-p1->point.y);

        Vec2 goal = vec2_mult(dir, line.length/2);
        Vec2 diff = vec2_sub(goal,vec2_mult(dir,(line.length-dist)/2 * elasticity));
        
        p1->point = vec2_add(p1->point,diff);
        p2->point = vec2_sub(p2->point, diff);
    }


}