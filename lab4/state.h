#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

enum states {
    INITIAL,
    DRAG_UP,
    VERTEX,
    DRAG_DOWN,
    FINAL
};

struct mouse_ev* mouse_get_event(struct packet *pp);

int state_machine(struct mouse_ev* event, uint8_t x_len, uint8_t tolerance);

#endif
