#include <stdio.h>
#include <math.h>

#include "allegro5/allegro_font.h"

#include "game.h"

double x = 0, y = 0;
int w = 100, h = 100;

ALLEGRO_FONT* default_font = NULL;
ALLEGRO_BITMAP* square = NULL;

void game_run() {
    al_init();
    al_init_font_addon();

    default_font = al_create_builtin_font();

    square = al_create_bitmap(w, h);
    al_set_target_bitmap(square);
    al_clear_to_color(al_map_rgba(255, 255, 255, 255));

    ALLEGRO_DISPLAY* display = al_create_display(512, 512);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

    al_register_event_source(queue, al_get_display_event_source(display));

    bool running = true;
    double previous_time = al_get_time();
    double current_time = previous_time;

    while (running) {

        previous_time = current_time;
        current_time = al_get_time();

        double delta = current_time - previous_time;

        ALLEGRO_EVENT event;
        while (al_get_next_event(queue, &event)) {
            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                running = false;
            }
        }

        game_update(delta);
        game_draw(delta);
    }

    printf("Hello world\n");
}

void game_update(double delta) {
    x += delta * 10;
    y += delta * 10;

    x = fmod(x, 255);
    y = fmod(y, 255);

}

void game_draw(double delta) {
    al_clear_to_color(al_map_rgba(0, 0, 0, 255));
    al_draw_bitmap(square, x, y, 0);
    al_draw_textf(default_font, al_map_rgba(255, 255, 0, 255), 0, 0, ALLEGRO_ALIGN_LEFT, "%.2f", 1.0 / delta);
    al_flip_display();
}
