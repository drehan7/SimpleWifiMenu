#ifndef _LAYOUT_H
#define _LAYOUT_H
#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "network.h"

#define WIDTH 1000
#define HEIGHT 800

// State of application
typedef struct {
        SSIDS* ssids;

        // Screen
        size_t screenW;
        size_t screenH;
        Font font;
} State ;

Vector2 state_init(void);
void state_update(void);
void state_load_font(char* font_path);

void state_ssid_prev_page(void);
void state_ssid_next_page(void);

void render_loading(void);

void render_config_panel(void);
void render_info_panel(void);





#endif //_LAYOUT_H
