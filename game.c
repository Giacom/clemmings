#include <stdio.h>
#include <math.h>

#include "allegro5/allegro_font.h"
#include "allegro5/allegro_image.h"

#include "game.h"
#include "lemming.h"
#include "world.h"
#include "input.h"

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

    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "resources");
    al_change_directory(al_path_cstr(path, '/'));  // change the working directory
    al_destroy_path(path);

    al_install_mouse();
    al_install_keyboard();

    default_font = al_create_builtin_font();

    lemming_sprite = al_load_bitmap("lemmings.png");
    if (!lemming_sprite) {
        printf("Error loading sprite.\n");
        return;
    }

    active_world = load_world("world.png");

    ALLEGRO_DISPLAY* display = al_create_display(screen_width, screen_height);
    al_set_window_title(display, "Lemmings");

    // Set Zoom for display
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_scale_transform(&transform, scale, scale);
    al_use_transform(&transform);

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());

    bool running = true;

    previous_time = al_get_time();
    current_time = previous_time;

    const static double running_fps = 1.0 / 60.0;

    while (running) {
        ticks++;

        if (delta < (current_time - previous_time)) {
            al_rest(running_fps - (current_time - previous_time));
        }

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

        update_mouse_states();

        game_update();
        game_draw();
    }
}

INPUT_RESULT game_handle_input(ALLEGRO_EVENT* event) {
    if (event->type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return QUIT_GAME;
    }
    if (event->type == ALLEGRO_EVENT_KEY_UP && event->keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
        return QUIT_GAME;
    }
    return NOTHING;
}

void game_update(void) {

    if (is_mouse_up(LEFT_MOUSE_BUTTON)) {
        int x_range = 32, y_range = 32;
        int x = 0, y = 0;
        get_mouse_position(&x, &y);
        printf("click (%d %d)\n", x, y);
        destruct_collision(&active_world, x - x_range / 2, y - y_range / 2, x_range, y_range);
    }

    if (active_lemmings < MAX_LEMMINGS && current_time > last_spawn + spawn_time) {
        last_spawn = current_time;
        lemmings[active_lemmings++] = (LEMMING) { 128, 0, WALKING_RIGHT };
    }

    for (int i = 0; i < active_lemmings; i++) {
        lemming_update(&lemmings[i]);
    }

    update_bitmap_from_collision_map(&active_world);
}

void game_draw(void) {
    al_clear_to_color(al_map_rgba(0, 255, 255, 255));
    al_draw_bitmap(active_world.sprite, 0, 0, 0);

    al_hold_bitmap_drawing(true);
    for (int i = 0; i < active_lemmings; i++) {
        lemming_draw(&lemmings[i]);
    }
    al_hold_bitmap_drawing(false);

    if (DEBUG) {
        int x = 0, y = 0;
        get_mouse_position(&x, &y);
        al_draw_textf(default_font, al_map_rgba(255, 255, 0, 255), 0, 0, ALLEGRO_ALIGN_LEFT, "(%d, %d) %.0f", x, y, 1.0 / delta);
    }
    al_flip_display();
}
