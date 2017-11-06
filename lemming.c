#include "lemming.h"
#include "game.h"
#include "world.h"

const int max_lemmings = 255;
LEMMING lemmings[max_lemmings];

int active_lemmings = 0;
const double spawn_time = 1.0;
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

    bool is_colliding_on_floor = is_collision(&active_world, lemming->x, lemming->y + 1);
    if (!is_colliding_on_floor) {
        lemming->y += 1;
        return;
    }

    if (lemming->state == WALKING_LEFT) {
        lemming->x -= 1;
    }

    if (lemming->state == WALKING_RIGHT) {
        lemming->x += 1;
    }
}
