#include "layout.h"

static State *state = NULL;
static ScrollingComponent *m_ScrollComponent = NULL;
static InfoComponent* m_InfoComponent = NULL;
static Rectangle m_NavContainer;

// TODO: not sure what else to do with this
bool state_ok() {
        return (state->ready && !WindowShouldClose() && IsFontReady(state->font));
}

/* Loading text displayed while fetching networks*/
void render_loading(void)
{
        ClearBackground(BLACK);
        char* loading_text = "Loading...";

        BeginDrawing();

                DrawText(loading_text, (state->screenW / 2)-strlen(loading_text), (state->screenH / 2), 30, RED);

        EndDrawing();
}

void render_page_count(void)
{
        char* total_networks = malloc(50 * sizeof(char));
        sprintf(total_networks, "Total networks: %ld", state->ssids->count);

        char* page_number = malloc(15 * sizeof(char));
        size_t curr_page_num = state->ssids->page;

        sprintf(page_number, "Page: %ld", curr_page_num + 1);
        
        DrawTextEx(state->font, page_number, (Vector2){30, state->screenH - 40}, 30, 2, GREEN);
        DrawTextEx(state->font, total_networks, (Vector2){150, state->screenH - 40}, 30, 2, GREEN);
}

PositionSettings* init_position_settings(size_t ssid_count)
{
        PositionSettings* pos = malloc(1 * sizeof(*pos));

        if (pos == NULL) 
        {
                printf("Could not allocate memory -- %s\n", __func__);
                exit(1);
        }

        // m_InfoContainer = (Rectangle) {
        //         .x         = INFO_CONTAINERX,
        //         .y         = INFO_CONTAINERY,
        //         .width     = (int)(WIDTH / 2),
        //         .height    = (int)(HEIGHT / 4) * 3,
        // };

        m_NavContainer = (Rectangle) {
                .x         = SSID_CONTAINERX,
                .y         = SSID_CONTAINERY + 50,
                .width     = SSID_CONTAINERW,
                .height    = (HEIGHT - SSID_CONTAINERH) / 2,
        };


        return pos;
}

Vector2 state_init(void)
{
        state = malloc(sizeof(*state));

        if (state == NULL) 
        {
                printf("Error: Could not allocate enough memory.");
                exit(1);
        }

        memset(state, 0, sizeof(*state));

        SSIDS* _ssids = get_ssids();
        state->ssids = _ssids;
        state->screenW = WIDTH;
        state->screenH = HEIGHT;
        state->appcolor = MYCOLOR;
        state->ready = false;

        state->layout = init_position_settings(_ssids->count);

        Rectangle scroll_layout = {
                .x         = SSID_CONTAINERX,
                .y         = SSID_CONTAINERY,
                .width     = SSID_CONTAINERW,
                .height    = SSID_CONTAINERH
        };

        Rectangle _layout = {
                .x         = INFO_CONTAINERX,
                .y         = INFO_CONTAINERY,
                .width     = INFO_CONTAINERW,
                .height    = INFO_CONTAINERH,
        };

        m_ScrollComponent = init_scrolling_component(scroll_layout, _ssids->count);
        m_InfoComponent = init_info_component(_layout);

        printf("State init complete: %ld\n", _ssids->count);
        state->ready = true;


        return (Vector2) { .x = WIDTH, .y = HEIGHT };
}

// void update_info_container()
// {
//         int ssidx = m_ScrollContainer->selected_idx;
//         char* sname;
//         Rectangle ic_layout = m_InfoContainer->layout;
//         int x = ic_layout.x + ((ic_layout.width / 2) - strlen(sname));
//         int y = ic_layout.y + ic_layout.height / 3;
//
//         if ( ssidx >= 0 ) {
//                 sname = state->ssids->ssid_list[ssidx];
//         } else {
//                 sname = "Click network.";
//         }
//
//
//         DrawText(sname, x, y, 25, SKYBLUE);
// }

void state_load_font(char* font_path) 
{
        if (state != NULL) 
                state->font = LoadFont(font_path);
}

void state_update(void)
{
        // Timeout at some point
        while (state->ssids == NULL) {
                render_loading();
        }

        ClearBackground(state->appcolor);
        BeginDrawing();

                // Starting Position for Wifi Networks
                int x = SSID_CONTAINERX + SSID_MARGIN;
                int y = SSID_CONTAINERY + SSID_MARGIN;

                // Update Components
                update_scrolling_component(m_ScrollComponent, state->ssids);
                update_info_component(m_InfoComponent, state->ssids, m_ScrollComponent->selected_idx);
                

                // Vector2 mouse_pos = GetMousePosition();
                
                // EXIT PROGRAM
                if (IsKeyPressed(KEY_Q)) {
                        exit(1);
                }

                render_page_count();

        EndDrawing();
}
