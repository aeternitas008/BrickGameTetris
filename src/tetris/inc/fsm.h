#ifndef FSM_H
#define FSM_H

#include "defines.h"
#include "objects.h"
#include "frog_backend.h"
#include "frog_frontend.h"

typedef enum
{
    // MAIN = 0,
    START = 0,
    SPAWN,
    MOVING,
    SHIFTING,
    REACH,
    FELL,
    GAMEOVER,
    EXIT_STATE
} state_t;

typedef enum
{
    MOVE_UP = 0,
    MOVE_DOWN,
    MOVE_RIGHT,
    MOVE_LEFT,
    ESCAPE_BTN,
    ENTER_BTN,
    NOSIG,
    SPACE_BTN
} signals;

signals get_signal(int user_input);
void sigact(signals sig, state_t *state, game_stats_t *stats, board_t *map, tetramino_pos *tetramino_pos);

#endif