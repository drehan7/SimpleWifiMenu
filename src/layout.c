#include "layout.h"

static State *state = NULL;
static ScrollingComponent *m_ScrollContainer = NULL;
static Rectangle m_InfoContainer;
static Rectangle m_NavContainer;

// void state_ssid_prev_page(void)
// {
// // TODO: impl
// }

// void check_ssid_clicked(Vector2* mouse_pos)
// {
// }

// TODO: not sure what else to do with this
bool state_ok()
{
        return (!WindowShouldClose() && IsFontReady(state->font));
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

        m_InfoContainer = (Rectangle) {
                .x         = INFO_CONTAINERX,
                .y         = INFO_CONTAINERY,
                .width     = (int)(WIDTH / 2),
                .height    = (int)(HEIGHT / 4) * 3,
        };

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

        state->layout = init_position_settings(_ssids->count);

        Rectangle scroll_layout = {
                .x         = SSID_CONTAINERX,
                .y         = SSID_CONTAINERY,
                .width     = SSID_CONTAINERW,
                .height    = SSID_CONTAINERH
        };

        m_ScrollContainer = init_scrolling_component(scroll_layout, _ssids->count);

        printf("State init complete: %ld\n", _ssids->count);


        return (Vector2) { .x = WIDTH, .y = HEIGHT };
}

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

                update_scrolling_container(m_ScrollContainer);
                
                Vector2 mouse_pos = GetMousePosition();
                
                // User clicked back or next button
                // if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                // {
                //
                // }

                // EXIT PROGRAM
                if (IsKeyPressed(KEY_Q)) {
                        exit(1);
                }

                render_page_count();

        EndDrawing();
}
