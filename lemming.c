#include "lemming.h"
#include "game.h"
#include "world.h"

LEMMING lemmings[MAX_LEMMINGS];

int active_lemmings = 0;
const double spawn_time = 0.1;
double last_spawn = 0.0;

ALLEGRO_BITMAP* lemming_sprite = NULL;

const int sprite_width = 5;
const int sprite_height = 8;

void lemming_draw(LEMMING* lemming) {
    if (lemming->state == DEAD) {
        return;
    }

    int flags = 0;
    if (lemming->state == WALKING_LEFT) {
        flags = ALLEGRO_FLIP_HORIZONTAL;
    }
    al_draw_bitmap_region(lemming_sprite, 0, 0, sprite_width, sprite_height, lemming->x - (sprite_width / 2), lemming->y - sprite_height + 1, flags);
}

void lemming_update(LEMMING* lemming) {
    if (lemming->state == DEAD) {
        return;
    }

    int new_x = lemming->x;
    int new_y = lemming->y;

    bool is_colliding_on_floor = is_collision(&active_world, lemming->x, lemming->y + 1);
    if (!is_colliding_on_floor) {
        new_y += 1;
    } else if (lemming->state == WALKING_LEFT || lemming->state == WALKING_RIGHT) {
        int modifier = lemming->state == WALKING_LEFT ? -1 : 1;

        bool blocked = true;
        for (int y = 0; y < 3; y++) {
            int test_x = lemming->x + modifier;
            int test_y = lemming->y - y;
            bool is_colliding_wall = is_collision(&active_world, test_x, test_y);
            if (!is_colliding_wall) {
                blocked = false;
                new_x = test_x;
                new_y = test_y;
                break;
            }
        }

        if (blocked) {
            lemming->state = lemming->state == WALKING_LEFT ? WALKING_RIGHT : WALKING_LEFT;
        }
    }

    lemming->x = new_x;
    lemming->y = new_y;
}
