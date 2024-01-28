#ifndef _LAYOUT_H
#define _LAYOUT_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "network.h"
#include "scrolling.h"
#include "info.h"

// Move these to some config ???
#define MYCOLOR CLITERAL(Color){ 39,54,67,255 }

#define WIDTH 1000
#define HEIGHT 800

#define MAX_PER_PAGE 5

#define SSID_CONTAINERX 20
#define SSID_CONTAINERY 50
#define SSID_CONTAINERW (int)(WIDTH / 3)
#define SSID_CONTAINERH (int)((HEIGHT / 4) * 3)
#define SSID_MARGIN 20

#define INFO_CONTAINERX 400
#define INFO_CONTAINERY 50
#define INFO_CONTAINERW (int)(WIDTH / 2)
#define INFO_CONTAINERH (int)(HEIGHT / 4) * 3


typedef struct {

        Rectangle back_button;
        Rectangle next_button;

} PositionSettings;

// State of application
typedef struct {
        bool ready;

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
bool state_ok(void);
void state_update(void);
void state_load_font(char* font_path);

void render_loading(void);

PositionSettings* init_position_settings(size_t ssid_count);

#endif //_LAYOUT_H
