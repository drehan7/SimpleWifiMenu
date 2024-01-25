#include "scrolling.h"


/*
 Check bounds of first and last 
 item to make sure we are within the container
*/
bool check_scrolling(ScrollingComponent* sc, int scroll_move)
{
        bool do_scroll = true;

        size_t len = sc->children_count;
        if ( len == 0 ) return;

        Rectangle rfirst = sc->items[0];
        Rectangle rlast = sc->items[len-1];
        Rectangle layout = sc->pc;

        // first item cant go down more
        // last item cant go up more

        if ( (rfirst.y + scroll_move) > (layout.y + (rfirst.height/2)) || 
                (rlast.y + rlast.height + scroll_move) < layout.height ) 
        {
                do_scroll = false;
        }

        return do_scroll;
}

bool display_rect(Rec r, Rec layout)
{
        return ( r.y < layout.height && r.y > layout.y );
}

// Container (rect) containing a list of rectangles for each ssid button
ScrollingComponent* init_scrolling_component(Rectangle layout, size_t ssid_count)
{
        ScrollingComponent* scmpt = malloc(1*sizeof(ScrollingComponent));

        // Parent Container
        scmpt->pc = layout;

        scmpt->items = malloc(ssid_count * sizeof(Rectangle));
        scmpt->children_count = ssid_count;

        // Todo come up with math for responsive UI
        int buttonw = 300;
        int buttonh = 40;

        int start_posy = layout.y + 10;
        int start_posx = layout.x + 15;
        int np = buttonh;

        Rectangle nrect;
        for (size_t i = 0; i < ssid_count; ++i)
        {
                nrect = (Rectangle) {
                        .x = start_posx,
                        .y = start_posy,
                        .width = buttonw,
                        .height = buttonh,
                };

                start_posy += 50;
                scmpt->items[i] = nrect;
        }

        return scmpt;
}

void update_scrolling_container(ScrollingComponent* sc)
{
        // TODO: move this to define
        int ss = 6; // scroll speed

        DrawRectangleLinesEx(sc->pc, 0.7f, YELLOW);

        int scroll_move = (GetMouseWheelMove() * ss);

        bool do_scroll = check_scrolling(sc, scroll_move);

        for (size_t i = 0; i < sc->children_count; ++i)
        {
                // handle_scrolling(sc, scroll_move, i);
                if ( do_scroll ) {
                        sc->items[i].y += scroll_move;
                }

                // Hide overflowing items
                if (display_rect( sc->items[i], sc->pc )) 
                {

                        Color c = (i % 2 == 0) ? RED : BLUE;
                        DrawRectangleLinesEx(sc->items[i], 0.7f, c);
                }

        }

}
