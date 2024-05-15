#pragma once

#include <stdio.h>
#include "types.h"

#define ERROR_EXIT(...) { fprintf(stderr, __VA_ARGS__); exit(1); }
#define ERROR_RETURN(R, ...) { fprintf(stderr, __VA_ARGS__); return R; }

#define SMOL 0.000000000000000000000000000000000000000000001;


//Returns a random number between [start,end)
i32 random_range(i32 start, i32 end);

//Delays the program for given amount of milliseconds.
void delay(i32 millisec);

f32 sign(f32 num);
