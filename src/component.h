#ifndef COMPONENT_H
#define COMPONENT_H
#include <raylib.h>
#include <stddef.h>
#include <stdlib.h>
#include "network.h"

typedef Rectangle Rec;

typedef struct {

        Rec pc; // Parent Container
        Rec* items; // List of items as Rects
        size_t children_count;
        int selected_idx;
        
} ScrollingComponent;

#endif // COMPONENT_H
