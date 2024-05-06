#pragma once

#include <stdio.h>
#include "types.h"

#define ERROR_EXIT(...) { fprintf(stderr, __VA_ARGS__); exit(1); }
#define ERROR_RETURN(R, ...) { fprintf(stderr, __VA_ARGS__); return R; }

i32 random_range(i32 start, i32 end);