#ifndef INPUT_H
#define INPUT_H

#include "allegro5/allegro.h"

#define MAX_MOUSE_BUTTONS 8


void update_mouse_states(void);
bool is_mouse_up(int button);
bool is_mouse_down(int button);
bool is_mouse_pressed(int button);
bool is_mouse_released(int button);

#endif // INPUT_H
