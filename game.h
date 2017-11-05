#ifndef GAME_H
#define GAME_H

#include "allegro5/allegro.h"

typedef enum {
    QUIT_GAME,
    NOTHING
} INPUT_RESULT;


void game_run(void);
INPUT_RESULT game_handle_input(ALLEGRO_EVENT* event);
void game_update(void);
void game_draw(void);

#endif // GAME_H
