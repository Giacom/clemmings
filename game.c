#include <stdio.h>
#include <math.h>

#include "allegro5/allegro_font.h"
#include "allegro5/allegro_image.h"

#include "game.h"
#include "lemming.h"

int scale = 4;
int screen_width = 1024, screen_height = 512;

long ticks = 0;
double delta = 0.0;
double current_time;
double previous_time;

ALLEGRO_FONT* default_font = NULL;

void game_run() {
    al_init();
    al_init_font_addon();
    al_init_image_addon();

    default_font = al_create_builtin_font();

    lemming_sprite = al_load_bitmap("lemmings.tga");
    if (!lemming_sprite) {
        printf("Error loading sprite.\n");
        return;
    }

    ALLEGRO_DISPLAY* display = al_create_display(screen_width, screen_height);
    al_set_window_title(display, "Lemmings");

    // Set Zoom for display
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_scale_transform(&transform, scale, scale);
    al_use_transform(&transform);

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

    al_register_event_source(queue, al_get_display_event_source(display));

    bool running = true;

    previous_time = al_get_time();
    current_time = previous_time;

    while (running) {
        ticks++;
        previous_time = current_time;
        current_time = al_get_time();

        delta = current_time - previous_time;

        ALLEGRO_EVENT event;
        while (al_get_next_event(queue, &event)) {
            INPUT_RESULT result = game_handle_input(&event);
            if (result == QUIT_GAME) {
                running = false;
            }
        }

        game_update();
        game_draw();
    }
}

INPUT_RESULT game_handle_input(ALLEGRO_EVENT* event) {
    if (event->type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return QUIT_GAME;
    }
    return NOTHING;
}

void game_update(void) {
    if (active_lemmings < max_lemmings && current_time > last_spawn + spawn_time) {
        last_spawn = current_time;
        lemmings[active_lemmings++] = (LEMMING) { 128, 0, WALKING_RIGHT };
    }
    for (int i = 0; i < active_lemmings; i++) {
        lemming_update(&lemmings[i]);
    }
}

void game_draw(void) {
    al_clear_to_color(al_map_rgba(0, 255, 255, 255));
    for (int i = 0; i < active_lemmings; i++) {
        lemming_draw(&lemmings[i]);
    }
    al_draw_textf(default_font, al_map_rgba(255, 255, 0, 255), 0, 0, ALLEGRO_ALIGN_LEFT, "%.0f", 1.0 / delta);
    al_flip_display();
}
