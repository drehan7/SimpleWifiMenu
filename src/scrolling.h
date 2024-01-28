#ifndef SCROLLING_COMPONENT
#define SCROLLING_COMPONENT
#include "component.h"

#define SCROLLSPEED 10

ScrollingComponent* init_scrolling_component(Rec layout, size_t ssid_count);
void update_scrolling_component(ScrollingComponent* sc, SSIDS* ssids);

bool check_scrolling(ScrollingComponent* sc, int scroll_move);
bool show_rect(Rec r, Rec layout);


#endif // SCROLLING_COMPONENT
