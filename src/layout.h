#ifndef _LAYOUT_H
#define _LAYOUT_H
#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "network.h"

#define MYCOLOR CLITERAL(Color){ 39,54,67,255 }

#define WIDTH 1000
#define HEIGHT 800

#define SSID_CONTAINERX 20
#define SSID_CONTAINERY 50

#define INFO_CONTAINERX 400
#define INFO_CONTAINERY 50

#define INFO_CONTAINERW 500


typedef struct {

        Rectangle ssid_container;
        Rectangle info_container;
        Rectangle nav_container;
        Rectangle back_button;
        Rectangle next_button;

} PositionSettings;


// State of application
typedef struct {
        SSIDS* ssids;

        // Screen
        size_t screenW;
        size_t screenH;
        Font font;
        Color appcolor;

        // Containers
         PositionSettings* layout;
} State ;


Vector2 state_init(void);
bool state_ok();
void state_update(void);
void state_load_font(char* font_path, int font_size);

void state_ssid_prev_page(void);
void state_ssid_next_page(void);

void render_loading(void);
void render_layout();

void render_config_panel(void);
void render_info_panel(void);

PositionSettings* init_position_settings();





#endif //_LAYOUT_H
