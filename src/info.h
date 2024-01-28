#ifndef INFO_H
#define INFO_H
#include "component.h"

#define SCROLL_SPEED 4


typedef struct {
        Rectangle layout;
        char* text;
} Title;

typedef struct {
        Rectangle layout;
        Title* title;
} InfoComponent;


InfoComponent* init_info_component(Rectangle layout);

void update_info_component(InfoComponent* ic, SSIDS* ssids, size_t idx);
void update_title(Title* t, SSIDS* ssids, size_t idx);

#endif // !INFO_H
