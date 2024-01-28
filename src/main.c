// #include <string.h>
#include "network.h"
#include "layout.h"

#define WIDTH 1000
#define HEIGHT 800

// #define FONT_PATH "resources/Roboto-Regular.ttf"
#define FONT_PATH "resources/IBMPlexMono-Regular.ttf"
#define FONT_SIZE 12

int main()
{
        Vector2 screenXY = state_init();
        // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        InitWindow(screenXY.x, screenXY.y, "WiFi Gui");
        SetTargetFPS(60);

        state_load_font(FONT_PATH);

        while(state_ok())
        {
                state_update();
        }

        CloseWindow();

        return 0;
}
