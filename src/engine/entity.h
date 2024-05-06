#pragma once

#include "rect.h"
#include "types.h"
#include "render.h"

typedef struct {
    Rect rect;
    RenderData render_data;
} Entity;