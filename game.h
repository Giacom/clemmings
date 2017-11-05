#ifndef GAME_H
#define GAME_H

#include "allegro5/allegro.h"

enum InputResult {
    QUIT_GAME,
    NOTHING
};


void game_run(void);
enum InputResult game_handle_input(ALLEGRO_EVENT* event);
void game_update(double delta);
void game_draw(double delta);

#endif // GAME_H
