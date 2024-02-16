#include "info.h"

InfoComponent* init_info_component(Rectangle layout)
{
        InfoComponent* ic = malloc(1*sizeof(ic));
        ic->layout = layout;

        // Title
        Rectangle title_layout = {
                .x = layout.x,
                .y = layout.y,
                .width = layout.width,
                .height = (layout.height / 7),
        };
        char* t_text = "Network Information";

        Title* t_title = malloc(1 * sizeof(t_title));
        t_title->text = t_text;
        t_title->layout = title_layout;

        ic->title = t_title;

        return ic;
}

void update_title(Title* t, SSIDS* ssids, size_t idx)
{
        DrawRectangleLinesEx(t->layout, 0.7f, GREEN);
        DrawText(t->text, t->layout.width, t->layout.height, 30, BLACK);
}


void update_info_component(InfoComponent* ic, SSIDS* ssids, size_t idx)
{
        DrawRectangleLinesEx(ic->layout, 0.7f, SKYBLUE);

        update_title(ic->title, ssids, idx);

}
