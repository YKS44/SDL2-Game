#include "../util.h"
#include "../types.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

//returns a random integer from [start,end)
i32 random_range(i32 start, i32 end){
    return rand() % (end-start) + start;
}

void delay(i32 millisec){
    i32 startTime = clock();
    
    while(clock() < startTime + millisec);
}