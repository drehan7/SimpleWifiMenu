#include <string.h>
#include "network.h"
#include "layout.h"

#define WIDTH 1000
#define HEIGHT 800


// #define DEBUG 0
void Render(Rectangle* rect, SSIDS* ssids);
void Render(Rectangle* rect, SSIDS* ssids)
{
        ClearBackground(BLACK);
        BeginDrawing();
                // Draw Container
                // #ifdef DEBUG
                        // DrawLine(0, (HEIGHT/2), WIDTH -1, (HEIGHT / 2), GREEN); // HORIZONTAL DEBUG LINE
                        // DrawLine((WIDTH/2), 0, (WIDTH/2), HEIGHT-1, BLUE); // VERTICAL
                        // DrawRectangleLinesEx(*container, 0.7f, RED);
                // #endif

                // Render buttons for 5 networks
                int x = 20;
                int y = 50;
                printf("Total networks: %d\n", ssids->count);
                size_t start_idx = ssids->page * 5;
                printf("Startidx: %d\n", start_idx);
                printf("Network at idx: %s\n", ssids->ssids[start_idx]);
                for (size_t i = start_idx; i < 5; ++i)
                {
                        Rectangle button = { .width = 300, .height = 75, .x = x, .y = y };
                        DrawRectangleLinesEx(button, 0.7f, RED);
                        DrawText(ssids->ssids[i], x + 30, y+20, 25, RAYWHITE);
                        
                        y = y + 150;
                }
                // WUD NOTE: For next starting idx, mult 5 by page

        EndDrawing();
}

void loop(Rectangle* container, SSIDS* ssids);

void loop(Rectangle* container, SSIDS* ssids)
{
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        InitWindow(WIDTH, HEIGHT, "WiFi Gui");


        int rendered = 0;

        size_t page = 0;
        while(!WindowShouldClose())
        {
                Rectangle main_container = { .x = 0, .y = 0, .width = WIDTH, .height = HEIGHT };

                DrawRectangleRec(main_container, RED);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                        ClearBackground(BLACK);
                        // ssids->page++;
                        // printf("page: %d\n", ssids->page);
                }

                Render(&main_container, ssids);
        }

        CloseWindow();

}

int main()
{

        Rectangle container= {
                .width   = (int)(WIDTH / 2.2f),
                .height  = (int)(HEIGHT/1.3),
                .x       = (int)((WIDTH/2) - ((WIDTH/2.2f)/2)),
                .y       = 50,
        };


        // for (size_t i = 0; i < ssids->count; ++i)
        // {
        //         printf("Network is %s\n", ssids->ssids[i]);
        // }
        SSIDS* ssids = get_ssids();


        // Main Game Driver
        loop(&container, ssids);

        return 0;
}
