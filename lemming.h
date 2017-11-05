#ifndef LEMMING_H
#define LEMMING_H

#include "allegro5/allegro.h"

typedef enum {
    WALKING_RIGHT,
    WALKING_LEFT,
    BLOCKING,
    DEAD
} LEMMING_STATE;

typedef struct {
    int x, y;
    LEMMING_STATE state;
} LEMMING;

extern const int max_lemmings;
extern LEMMING lemmings[];

extern int active_lemmings;
extern const double spawn_time;
extern double last_spawn;

ALLEGRO_BITMAP* lemming_sprite;


void lemming_draw(LEMMING* lemming);
void lemming_update(LEMMING* lemming);

#endif // LEMMING_H
