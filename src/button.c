#include <stdio.h>
#include <raylib.h>

#define BTN_WIDTH 10
#define BTN_HEIGHT 20

Rectangle create_button(int width, int height, int posx, int posy)
{
        Rectangle button;

        button.width = width;
        button.height = height;
        button.x = posx;
        button.y = posy;

        return button;
}
