#include "lemming.h"
#include "game.h"

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
    al_draw_bitmap_region(lemming_sprite, 0, 0, sprite_width, sprite_height, lemming->x, lemming->y, flags);
}

void lemming_update(LEMMING* lemming) {
    if (lemming->state == DEAD) {
        return;
    }

    if (lemming->state == WALKING_LEFT) {
        lemming->x -= 1;
    }

    if (lemming->state == WALKING_RIGHT) {
        lemming->x += 1;
    }
}
