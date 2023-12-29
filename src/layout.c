#include "layout.h"

static State *state = NULL;

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

void render_layout()
{
        // DEBUG - layout containers
        DrawRectangleLinesEx(state->layout->ssid_container, 0.7f, YELLOW);
        DrawRectangleLinesEx(state->layout->info_container, 1.5f, MAGENTA);
        DrawRectangleLinesEx(state->layout->nav_container, 1.5f, RED);

        // Nav Buttons
        DrawRectangleLinesEx(state->layout->back_button, 0.7f, GREEN);
        DrawRectangleLinesEx(state->layout->next_button, 0.7f, GREEN);
        
        DrawTextEx(state->font, "Back",
                        (Vector2)
                        {
                                state->layout->back_button.x+10,
                                state->layout->back_button.y+5
                        },
                30, 2, RAYWHITE );

        DrawTextEx(state->font, "Next",
                        (Vector2)
                        {
                                state->layout->next_button.x+10,
                                state->layout->next_button.y+5
                        },
                30, 2, RAYWHITE );
}

void render_page_count(void)
{
        char* total_networks = malloc(50 * sizeof(char));
        sprintf(total_networks, "Total networks: %ld", state->ssids->count);

        char* page_number = malloc(15 * sizeof(char));
        size_t curr_page_num = state->ssids->page;

        sprintf(page_number, "Page: %d", curr_page_num + 1);
        
        DrawTextEx(state->font, page_number, (Vector2){30, state->screenH - 40}, 30, 2, GREEN);
        DrawTextEx(state->font, total_networks, (Vector2){150, state->screenH - 40}, 30, 2, GREEN);
        
        // free(total_networks);
        // free(page_number);
}

void render_page_buttons(void)
{
        // Rectangle b_button = { .width = 100, .height = 75, .x = x, .y = (sta) };
        // Rectangle n_button = { .width = 100, .height = 75, .x = x+150, .y = y+50 };
        // DrawRectangleLinesEx(b_button, 0.7f, GREEN);
        // DrawRectangleLinesEx(n_button, 0.7f, GREEN);
        // 
        // DrawTextEx(state->font, "Back", (Vector2){b_button.x+10, b_button.y+5}, 30, 2, RAYWHITE );
        // DrawTextEx(state->font, "Next", (Vector2){n_button.x+10, n_button.y+5}, 30, 2, RAYWHITE );
}

// Maybe good to store these in state ??
// For quick access to position or buttons
void render_info_panel(void)
{
        Rectangle container = {
                .x = 400,
                .y = 50 + 750,
                .width = 500,
                .height = 200,
        };
        DrawRectangleLinesEx(container, 1.5f, SKYBLUE);
}

PositionSettings* init_position_settings()
{
        PositionSettings* pos = malloc(1 * sizeof(*pos));

        if (pos == NULL) 
        {
                printf("Could not allocate memory -- init_position_settings()\n");
                exit(1);
        }

        Rectangle ssid_container = {
                .x         = SSID_CONTAINERX,
                .y         = SSID_CONTAINERY,
                .width     = (int)(state->screenW / 3),
                .height    = (int)((state->screenH / 4) * 3),
        };

        Rectangle info_container = {
                .x         = INFO_CONTAINERX,
                .y         = INFO_CONTAINERY,
                .width     = (int)(WIDTH / 2),
                .height    = (int)(HEIGHT / 4) * 3,
        };

        Rectangle nav_container = {
                .x         = ssid_container.x,
                .y         = ssid_container.height + 50,
                .width     = ssid_container.width,
                .height    = (HEIGHT - ssid_container.height) / 2,
        };

        Rectangle b_button = { 
                .width     = nav_container.width / 4,
                .height    = nav_container.height - 10,
                .x         = nav_container.x + 10,
                .y         = nav_container.y + 10,
        };

        Rectangle n_button = { 
                .width     = nav_container.width / 4,
                .height    = nav_container.height - 10,
                .x         = b_button.x + (nav_container.width / 2),
                .y         = nav_container.y + 10,
        };

        pos->ssid_container = ssid_container;
        pos->info_container = info_container;
        pos->nav_container = nav_container;
        pos->back_button = b_button;
        pos->next_button = n_button;

        return pos;
}

Vector2 state_init(void)
{
        state = malloc(sizeof(*state));
        if (state == NULL) {
                printf("Error: Could not allocate enough memory.");
                exit(1);
        }
        memset(state, 0, sizeof(*state));

        state->ssids = get_ssids();
        state->screenW = WIDTH;
        state->screenH = HEIGHT;
        state->appcolor = MYCOLOR;

        state->layout = init_position_settings();

        printf("State init complete: %d\n", state->ssids->count);

        return (Vector2) { .x = WIDTH, .y = HEIGHT };
}

void state_load_font(char* font_path) 
{
        if (state != NULL) 
                state->font = LoadFont(font_path);
}

void state_update(void)
{
        while (state->ssids == NULL)
                render_loading();

        // Debug stuff. might extend
        if (IsKeyPressed(KEY_R))
        {
                ClearBackground(BLACK);
                refresh_ssids(state->ssids, 5); // TODO come up with default count
        }

        ClearBackground(state->appcolor);
        BeginDrawing();

                // Draw containers and buttons
                // render_layout();

                // Starting Position for Wifi Networks
                int x = SSID_CONTAINERX + 20;
                int y = SSID_CONTAINERY + 20;

                // TODO: render ssids in grid format

                // TODO: organize this better
                // Render Networks in ssid_container
                size_t start_idx = state->ssids->page * 5;
                size_t end_idx = (start_idx + 5 > state->ssids->count) ? state->ssids->count-1 : start_idx + 5;
                for (size_t i = start_idx; i < end_idx; ++i)
                {
                        Rectangle button = { .width = 300, .height = 75, .x = x, .y = y };
                        DrawRectangleLinesEx(button, 0.7f, BLACK);
                        Vector2 text_pos = { .x = x+30, .y = y+20 };
                        DrawTextEx(state->font, state->ssids->ssid_list[i], text_pos, 30, 2, RAYWHITE );
                        
                        y = y + 100;
                }
                // WUD NOTE: For next starting idx, mult 5 by page

                Vector2 mouse_pos = GetMousePosition();
                
                // User clicked back or next button
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {

                        if (CheckCollisionPointRec(mouse_pos, state->layout->back_button) &&
                                                                state->ssids->page > 0)
                        {
                                state->ssids->page--;
                        }
                        else if (CheckCollisionPointRec(mouse_pos, state->layout->next_button)) 
                        {
                                size_t l_idx = state->ssids->count - 1;
                                size_t s_idx = (state->ssids->page + 1) * 5;
                                
                                if (l_idx > s_idx)
                                        state->ssids->page++;
                        }
                        else
                        {
                                // check_ssid_clicked(&mouse_pos);
                        }
                }

                render_page_count();

        EndDrawing();
}
