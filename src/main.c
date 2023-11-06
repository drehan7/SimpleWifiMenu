#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <string.h>

#include "button.c"
#include "layout.c"

#define WIDTH 1000
#define HEIGHT 800

int main()
{
        InitWindow(WIDTH, HEIGHT, "WiFi Gui");

        Rectangle container= {
                .width   = (int)(WIDTH / 2.2f),
                .height  = (int)(HEIGHT/1.3),
                .x       = (int)((WIDTH/2) - ((WIDTH/2.2f)/2)),
                .y       = 50,
        };

        while(!WindowShouldClose())
        {
                ClearBackground(BLACK);
                BeginDrawing();
                DrawLine(0, (HEIGHT/2), WIDTH -1, (HEIGHT / 2), GREEN); // HORIZONTAL DEBUG LINE
                DrawLine((WIDTH/2), 0, (WIDTH/2), HEIGHT-1, GREEN); // VERTICAL
                    DrawRectangleLinesEx(container, 0.7f, RED);
                EndDrawing();

        }

        CloseWindow();
        return 0;
}
