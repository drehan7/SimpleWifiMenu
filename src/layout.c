#include "layout.h"

static State *state = NULL;

void state_ssid_prev_page(void)
{

}

void render_loading(void)
{
        ClearBackground(BLACK);
        char* loading_text = "Loading...";

        BeginDrawing();

                DrawText(loading_text, (state->screenW / 2)-strlen(loading_text), (state->screenH / 2), 30, RED);

        EndDrawing();
}

void render_config_panel(void)
{
        Rectangle container = {
                .x = 450,
                .y = 50,
                .width = 500,
                .height = 700,
        };
        DrawRectangleLinesEx(container, 1.5f, RED);
}

void render_page_count(void)
{
        char* total_networks = malloc(50 * sizeof(char));
        sprintf(total_networks, "Total networks: %ld", state->ssids->count);

        char* page_number = malloc(15 * sizeof(char));
        size_t curr_page_num = state->ssids->page;
        sprintf(page_number, "Page: %d", curr_page_num + 1);
        
        DrawTextEx(state->font, page_number, (Vector2){30, state->screenH - 40}, 30, 2, GREEN);
        DrawTextEx(state->font, total_networks, (Vector2){30, state->screenH - 70}, 30, 2, GREEN);
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


        printf("State init complete: %d\n", state->ssids->count);

        return (Vector2) { .x = WIDTH, .y = HEIGHT };
}

void state_load_font(char* font_path)
{
        state->font = LoadFont(font_path);
}

void state_update(void)
{
        while (state->ssids == NULL)
                render_loading();

        if (IsKeyPressed(KEY_R))
        {
                ClearBackground(BLACK);
                refresh_ssids(state->ssids, 5); // TODO come up with default count
        }
        //rgb(39,54,67)
        Color mycolor = (Color){39,54,67,255};

        ClearBackground(mycolor);
        BeginDrawing();

                // Starting Position for Wifi Networks
                int x = 20;
                int y = 50;
                int ssid_pos_y = y;

                size_t start_idx = state->ssids->page * 5;
                for (size_t i = start_idx; i < 5; ++i)
                {
                        Rectangle button = { .width = 300, .height = 75, .x = x, .y = y };
                        DrawRectangleLinesEx(button, 0.7f, BLACK);
                        // DrawText(state->ssids->ssids[i], x + 30, y+20, 25, RAYWHITE);
                        Vector2 text_pos = { .x = x+30, .y = y+20 };
                        DrawTextEx(state->font, state->ssids->ssid_list[i], text_pos, 30, 2, WHITE );
                        
                        y = y + 100;
                }
                // WUD NOTE: For next starting idx, mult 5 by page

                // TODO: Fix magic numbers
                x += 20;
                // Back & Next Buttons
                Rectangle b_button = { .width = 100, .height = 75, .x = x, .y = y+50 };
                Rectangle n_button = { .width = 100, .height = 75, .x = x+150, .y = y+50 };
                DrawRectangleLinesEx(b_button, 0.7f, GREEN);
                DrawRectangleLinesEx(n_button, 0.7f, GREEN);
                
                DrawTextEx(state->font, "Back", (Vector2){b_button.x+10, b_button.y+5}, 30, 2, RAYWHITE );
                DrawTextEx(state->font, "Next", (Vector2){n_button.x+10, n_button.y+5}, 30, 2, RAYWHITE );
                
                // User clicked back or next button
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                        Vector2 mouse_pos = GetMousePosition();

                        if (CheckCollisionPointRec(mouse_pos, b_button))
                        {
                                // state_ssid_prev_page();
                                if (state->ssids->page > 0) {
                                        state->ssids->page--;
                                        y = 50;
                                }
                                printf("BACK BUTTON\n");

                        }
                        else if (CheckCollisionPointRec(mouse_pos, n_button)) 
                        {
                                // state_ssid_next_page();
                                printf("NEXt BUTTON\n");
                                state->ssids->page++;
                                y = 50;
                        }
                }

                render_config_panel();
                render_page_count();
                // render_info_panel();

        EndDrawing();
}
