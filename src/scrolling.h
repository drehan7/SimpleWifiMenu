#ifndef SCROLLING_COMPONENT
#define SCROLLING_COMPONENT
#include <raylib.h>
#include <stddef.h>
#include <stdlib.h>
#include "network.h"

typedef Rectangle Rec;

typedef struct {

        Rec pc; // Parent Container
        Rec * items; // List of items as Rects
        size_t children_count;
        
} ScrollingComponent;


ScrollingComponent* init_scrolling_component(Rec layout, size_t ssid_count);
void update_scrolling_container(ScrollingComponent* sc, SSIDS* ssids);

bool check_scrolling(ScrollingComponent* sc, int scroll_move);
bool display_rect(Rec r, Rec layout);


#endif // SCROLLING_COMPONENT
