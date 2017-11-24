#ifndef INPUT_H
#define INPUT_H

#include "allegro5/allegro.h"

#define MAX_MOUSE_BUTTONS 8

#define LEFT_MOUSE_BUTTON 1
#define RIGHT_MOUSE_BUTTON 2

typedef ALLEGRO_MOUSE_STATE MOUSE_STATE;

void update_mouse_states(void);
bool is_mouse_up(int button);
bool is_mouse_down(int button);
bool is_mouse_pressed(int button);
bool is_mouse_released(int button);
void get_mouse_position(int *x, int *y);

#endif // INPUT_H
