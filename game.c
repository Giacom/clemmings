#include <stdio.h>
#include <math.h>

#include "allegro5/allegro_font.h"
#include "allegro5/allegro_image.h"

#include "game.h"

int scale = 4;
int screen_width = 1024, screen_height = 512;

double x = 0, y = 0;
int w = 20, h = 20;
long ticks = 0;

ALLEGRO_FONT* default_font = NULL;
ALLEGRO_BITMAP* square = NULL;

ALLEGRO_BITMAP* test_sprite = NULL;

void game_run() {
    al_init();
    al_init_font_addon();
    al_init_image_addon();

    default_font = al_create_builtin_font();

    square = al_create_bitmap(w, h);
    al_set_target_bitmap(square);
    al_clear_to_color(al_map_rgba(255, 255, 255, 255));

    test_sprite = al_load_bitmap("lemmings.tga");
    if (!test_sprite) {
        printf("Error loading sprite.\n");
        return;
    }

    ALLEGRO_DISPLAY* display = al_create_display(screen_width, screen_height);

    // Set Zoom for display
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_scale_transform(&transform, scale, scale);
    al_use_transform(&transform);

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

    al_register_event_source(queue, al_get_display_event_source(display));

    bool running = true;
    double previous_time = al_get_time();
    double current_time = previous_time;

    printf("%lu", sizeof(ALLEGRO_EVENT));

    while (running) {
        ticks++;
        previous_time = current_time;
        current_time = al_get_time();

        double delta = current_time - previous_time;

        ALLEGRO_EVENT event;
        while (al_get_next_event(queue, &event)) {
            enum InputResult result = game_handle_input(&event);
            if (result == QUIT_GAME) {
                running = false;
            }
        }

        game_update(delta);
        game_draw(delta);
    }
}

enum InputResult game_handle_input(ALLEGRO_EVENT* event) {
    if (event->type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return QUIT_GAME;
    }
    return NOTHING;
}

void game_update(double delta) {
    x += delta * 10;
    y += delta * 10;

    x = fmod(x, 255);
    y = fmod(y, 255);

}

void game_draw(double delta) {
    al_clear_to_color(al_map_rgba(0, 255, 255, 255));
    al_draw_bitmap(square, x, y, 0);
    al_draw_bitmap_region(test_sprite, 0, 0, 5, 8, x, y + h * 2, 0);
    al_draw_textf(default_font, al_map_rgba(255, 255, 0, 255), 0, 0, ALLEGRO_ALIGN_LEFT, "%.0f", 1.0 / delta);
    al_flip_display();
}
