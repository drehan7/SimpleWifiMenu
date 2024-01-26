#include "scrolling.h"

/*
 Check bounds of first and last 
 item to make sure we are within the container
*/
bool check_scrolling(ScrollingComponent* sc, int scroll_move)
{
        bool do_scroll = true;

        size_t len = sc->children_count;
        if ( len == 0 ) return false;

        Rec rfirst = sc->items[0];
        Rec rlast = sc->items[len-1];
        Rec layout = sc->pc;

        // first item cant go down more
        // last item cant go up more

        if ( (rfirst.y + scroll_move) > (layout.y + (rfirst.height/2)) || 
                (rlast.y + rlast.height + scroll_move) < layout.height ) 
        {
                do_scroll = false;
        }

        return do_scroll;
}

bool show_rect(Rec r, Rec layout)
{
        return ( r.y < layout.height && r.y > layout.y );
}

// Container (rect) containing a list of rectangles for each ssid button
ScrollingComponent* init_scrolling_component(Rec layout, size_t ssid_count)
{
        ScrollingComponent* scmpt = malloc(1*sizeof(ScrollingComponent));

        // Parent Container
        scmpt->pc = layout;

        scmpt->items = malloc(ssid_count * sizeof(Rec));
        scmpt->children_count = ssid_count;
        scmpt->selected_idx = -1;

        // Todo come up with math for responsive UI
        int buttonw = 300;
        int buttonh = 40;

        int start_posy = layout.y + 10;
        int start_posx = layout.x + 15;
        int np = buttonh;

        Rec nrect;
        for (size_t i = 0; i < ssid_count; ++i)
        {
                nrect = (Rec) {
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

void update_scrolling_container(ScrollingComponent* sc, SSIDS* ssids)
{
        // TODO: move this to define
        int ss = 6; // scroll speed

        DrawRectangleLinesEx(sc->pc, 0.7f, BLACK);

        int scroll_move = (GetMouseWheelMove() * ss);

        bool do_scroll = check_scrolling(sc, scroll_move);


        for (size_t i = 0; i < sc->children_count; ++i)
        {
                // handle_scrolling(sc, scroll_move, i);
                if ( do_scroll ) {
                        sc->items[i].y += scroll_move;
                }

                // Hide overflowing items
                if ( !show_rect( sc->items[i], sc->pc ) ) { continue; }


                // TODO NOW IDEA:
                //  Change sc `items` to modified Rect with `selected` flag
                // Mouse clicked and in button boundary

                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), sc->items[i]))
                {
                        sc->selected_idx = i;
                }

                if (i == sc->selected_idx) {
                        DrawRectangleLinesEx(sc->items[i], 0.7f, SKYBLUE);
                }
                else
                {
                        // Order matters here, i could just make the color but whatever
                        // Probably should TODO
                        DrawRectangleLinesEx(sc->items[i], 0.7f, RAYWHITE);
                        DrawRectangleLinesEx(sc->items[i], 0.7f, GRAY);
                }


                char* rtext = ssids->ssid_list[i];
                int x = sc->items[i].x + strlen(rtext);
                int y = (sc->items[i].y + (sc->items[i].height / 3));

                DrawText(rtext, x, y, 15, ORANGE);

        }

}
