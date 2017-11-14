#include "input.h"

typedef enum {
    MOUSE_RELEASED,
    MOUSE_PRESSED,
    MOUSE_UP,
    MOUSE_DOWN,
    MOUSE_ERROR
} MOUSE_BUTTON_STATE;

static MOUSE_BUTTON_STATE mouse_button_states[MAX_MOUSE_BUTTONS];

void update_mouse_states(void) {
    ALLEGRO_MOUSE_STATE state;
    al_get_mouse_state(&state);
    
    for (unsigned int button = 1; button <= MAX_MOUSE_BUTTONS; button++) {
        bool is_down = (state.buttons & button) != 0;
        MOUSE_BUTTON_STATE old_state = mouse_button_states[button];
        MOUSE_BUTTON_STATE new_state = old_state;

        if (old_state == MOUSE_RELEASED && is_down) {
            new_state = MOUSE_DOWN;
        } else if (old_state == MOUSE_PRESSED && !is_down) {
            new_state = MOUSE_UP;
        } else {
            if (old_state == MOUSE_DOWN && is_down) {
                new_state = MOUSE_PRESSED;
            } else if (old_state == MOUSE_UP && !is_down) {
                new_state = MOUSE_RELEASED;
            }
        }

        mouse_button_states[button] = new_state;
    }

    /*
    bool is_pressed = is_mouse_pressed(1);
    bool is_released = is_mouse_released(1);
    bool is_down = is_mouse_down(1);
    bool is_up = is_mouse_up(1);

    printf("pressed: %d - released: %d - down: %d - up: %d\n", is_pressed, is_released, is_down, is_up);
    */
}

bool is_mouse_up(int button) {
    return mouse_button_states[button] == MOUSE_UP;
}

bool is_mouse_down(int button) {
    return mouse_button_states[button] == MOUSE_DOWN;
}

bool is_mouse_pressed(int button) {
    return mouse_button_states[button] == MOUSE_DOWN || mouse_button_states[button] == MOUSE_PRESSED;
}

bool is_mouse_released(int button) {
    return mouse_button_states[button] == MOUSE_UP || mouse_button_states[button] == MOUSE_RELEASED;
}
